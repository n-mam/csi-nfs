#ifndef IDENTITY_HPP
#define IDENTITY_HPP

#include <csi.pb.h>
#include <csi.grpc.pb.h>

class IdentityService : public csi::v1::Identity::Service
{
  public:

    IdentityService()
    {
      iReady = true;
    }

    virtual grpc::Status GetPluginInfo(
      grpc::ServerContext *context,
      const csi::v1::GetPluginInfoRequest *request,
      csi::v1::GetPluginInfoResponse *response) override
    {
      response->set_name("nfs.csi.msystechnologies.com");
      response->set_vendor_version("0.1");
      return grpc::Status(grpc::StatusCode::OK, "GetPluginInfo");
    }

    virtual grpc::Status GetPluginCapabilities(
      grpc::ServerContext *context,
      const csi::v1::GetPluginCapabilitiesRequest *request,
      csi::v1::GetPluginCapabilitiesResponse *response) override
    {
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "GetPluginCapabilities");
    }

    virtual grpc::Status Probe(
      grpc::ServerContext *context,
      const csi::v1::ProbeRequest *request,
      csi::v1::ProbeResponse *response) override
    {
      google::protobuf::BoolValue *ready = (google::protobuf::BoolValue()).New();
      ready->set_value(iReady);
      response->set_allocated_ready(ready);
      return grpc::Status(grpc::StatusCode::OK, "Probe");
    }
  
  protected:

    bool iReady = false;

    std::string iName;

    std::string iVersion;
};


#endif