#ifndef NFSDRIVER_HPP
#define NFSDRIVER_HPP

#include <csi.pb.h>
#include <csi.grpc.pb.h>

#include <DriverBase.hpp>

#include <memory>
#include <string>

struct NFSVolume : public BaseVolume
{
  virtual ~NFSVolume(){}
  std::string server;
  std::string baseDir;
};

class CNFSDriver : public CBaseDriver
{
  public:

    virtual bool CreateVolume(const csi::v1::CreateVolumeRequest *request, csi::v1::CreateVolumeResponse *response) override
    {
      auto nfsVol = std::dynamic_pointer_cast<NFSVolume>(GetVolume(request->name()));

      if (nfsVol)
      {
        std::cout << "CNFSDriver::CreateVolume returning existing volume" << std::endl;
      }
      else
      {
        nfsVol = std::make_shared<NFSVolume>();

        try
        {
          nfsVol->name = request->name();
          nfsVol->server = request->parameters().at("server");
          nfsVol->baseDir = request->parameters().at("share");
        }
        catch(const std::exception& e)
        {
          std::cout << "CNFSDriver::CreateVolume : " << e.what() << std::endl;
          return false;
        }

        // mount server share

        std::string cmd = "mount -o nolock " + nfsVol->server + ":" + nfsVol->baseDir + " " + "/tmp";

        int rc = system(cmd.c_str());
      
        std::cout << cmd << " : " << rc << std::endl;

        if (rc != 0)
        {
          std::cout << "Failed to mount" << std::endl;
          return false;
        }

        // create subdirectory

        cmd = "mkdir –m 777 " + "/tmp/"s + nfsVol->name;

        rc = system(cmd.c_str());

        std::cout << cmd << " : " << rc << std::endl;

        if (rc != 0)
        {
          std::cout << "Failed to create volume sub-directory" << std::endl;
          system(std::string("umount -f -l /tmp").c_str());
          return false;
        }

        nfsVol->id = "[" + nfsVol->server + "][" + nfsVol->baseDir + "][" + nfsVol->name + "]";

        nfsVol->capacity_bytes = request->capacity_range().required_bytes();

        iVolumeMap[nfsVol->id] = nfsVol;
        iVolumeMap[nfsVol->name] = nfsVol;
      }

      auto csiVol = response->mutable_volume();

      csiVol->set_volume_id(nfsVol->id);

      csiVol->set_capacity_bytes(nfsVol->capacity_bytes);

      auto ctx = csiVol->mutable_volume_context();

      (*ctx)["server"] = nfsVol->server;
      (*ctx)["baseDir"] = nfsVol->baseDir;

      return true;
    }


  protected:


};

using SPCNFSDriver = std::shared_ptr<CNFSDriver>;

#endif