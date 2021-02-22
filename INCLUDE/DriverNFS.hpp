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
      bool fRet = false;

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
        return fRet;
      }

      std::string cmd;

      // mount the server's share
      cmd = "mount -o nolock " + server + ":" + share + " /tmp";
      int rc = system(cmd.c_str());
      std::cout << cmd << " : " << rc << std::endl;

      // create storage space name subdirectory
      cmd = "mkdir –m777 " + "/tmp/"s + ssname;
      rc = system(cmd.c_str());
      std::cout << cmd << " : " << rc << std::endl;

      return fRet;
    }


  protected:


};

using SPCNFSDriver = std::shared_ptr<CNFSDriver>;

#endif