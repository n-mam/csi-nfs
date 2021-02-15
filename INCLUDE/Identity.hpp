#ifndef IDENTITY_HPP
#define IDENTITY_HPP

#include <csi.pb.h>
#include <csi.grpc.pb.h>

#include <iostream>

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
      std::cout << "[IdentityService] GetPluginInfo" << std::endl;
      response->set_name("com.msystechnologies.csi.nfs");
      response->set_vendor_version("0.1");
      return grpc::Status(grpc::StatusCode::OK, "GetPluginInfo");
    }

    virtual grpc::Status GetPluginCapabilities(
      grpc::ServerContext *context,
      const csi::v1::GetPluginCapabilitiesRequest *request,
      csi::v1::GetPluginCapabilitiesResponse *response) override
    {
      std::cout << "[IdentityService] GetPluginCapabilities" << std::endl;
      auto cap = response->add_capabilities();
      cap->mutable_service()->set_type(csi::v1::PluginCapability_Service_Type_CONTROLLER_SERVICE);
      return grpc::Status(grpc::StatusCode::OK, "GetPluginCapabilities");
    }

    virtual grpc::Status Probe(
      grpc::ServerContext *context,
      const csi::v1::ProbeRequest *request,
      csi::v1::ProbeResponse *response) override
    {
      std::cout << "[IdentityService] Probe" << std::endl;
      response->mutable_ready()->set_value(iReady);
      return grpc::Status(grpc::StatusCode::OK, "Probe");
    }

  protected:

    bool iReady = false;

    std::string iName;

    std::string iVersion;
};


#endif