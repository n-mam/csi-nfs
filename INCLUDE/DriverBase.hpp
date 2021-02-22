#ifndef BASEDRIVER_HPP
#define BASEDRIVER_HPP

#include <csi.pb.h>
#include <csi.grpc.pb.h>

#include <memory>
#include <string>

using namespace std::string_literals;

class CBaseDriver
{
  public:

    CBaseDriver() {}
    ~CBaseDriver() {}

    virtual bool CreateVolume(const std::string& ssname, const google::protobuf::Map<std::string, std::string> &parameters)
    {
      return false;
    }

    virtual bool DeleteVolume(void)
    {
      return false;
    }
};

using SPCBaseDriver = std::shared_ptr<CBaseDriver>;

#endif