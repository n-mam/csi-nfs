#ifndef NFSDRIVER_HPP
#define NFSDRIVER_HPP

#include <csi.pb.h>
#include <csi.grpc.pb.h>

#include <DriverBase.hpp>

#include <memory>
#include <string>

class CNFSDriver : public CBaseDriver
{
  public:

    virtual bool CreateVolume(const std::string& ssname, const google::protobuf::Map<std::string, std::string> &parameters) override
    {
      std::string share;
      std::string server;

      try
      {
        server = parameters.at("server");
        share = parameters.at("share");
      }
      catch(const std::exception& e)
      {
        std::cout << "CNFSDriver::CreateVolume exception : " << e.what() << std::endl;
        return false;
      }

      std::string cmd;

      // mount server's share
      cmd = "mount -o nolock " + server + ":" + share + " /tmp";
      int rc = system(cmd.c_str());
      std::cout << cmd << " : " << rc << std::endl;

      // create storage space subdirectory
      if (rc == 0)
      {
        cmd = "mkdir –m 777 " + "/tmp/"s + ssname;
        rc = system(cmd.c_str());
        std::cout << cmd << " : " << rc << std::endl;
      }

      return ((rc == 0) ? true : false);
    }


  protected:


};

using SPCNFSDriver = std::shared_ptr<CNFSDriver>;

#endif