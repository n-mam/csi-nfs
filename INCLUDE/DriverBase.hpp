#ifndef BASEDRIVER_HPP
#define BASEDRIVER_HPP

#include <csi.pb.h>
#include <csi.grpc.pb.h>

#include <map>
#include <memory>
#include <string>

using namespace std::string_literals;

struct BaseVolume
{
  std::string id;
  std::string name;
  uint64_t capacity_bytes;
};

using SPBaseVolume = std::shared_ptr<BaseVolume>;

class CBaseDriver
{
  public:

    CBaseDriver() {}
    ~CBaseDriver() {}

    virtual bool CreateVolume(const csi::v1::CreateVolumeRequest *request, csi::v1::CreateVolumeResponse *response)
    {
      return false;
    }

    virtual bool DeleteVolume(void)
    {
      return false;
    }
  
    auto GetVolume(const std::string& key)
    {
      SPBaseVolume volume;

      try
      {
        volume = iVolumeMap.at(key);
      }
      catch(const std::exception& e)
      {
        std::cout << "GetVolume [" << key << "] not found" << std::endl;
      }

      return volume;
    }

  protected:

    std::map<std::string, SPBaseVolume> iVolumeMap;
    
};

using SPCBaseDriver = std::shared_ptr<CBaseDriver>;

#endif