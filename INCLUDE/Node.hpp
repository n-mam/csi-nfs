#ifndef NODE_HPP
#define NODE_HPP

#include <csi.pb.h>
#include <csi.grpc.pb.h>

#include <iostream>

class NodeService : public csi::v1::Node::Service
{
  public:

    virtual grpc::Status NodeStageVolume(
      grpc::ServerContext *context,
      const csi::v1::NodeStageVolumeRequest *request,
      csi::v1::NodeStageVolumeResponse *response) override
    {
      std::cout << "IdentityService [NodeStageVolume]\n";
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "NodeStageVolume");
    }

    virtual grpc::Status NodeUnstageVolume(
      grpc::ServerContext *context,
      const csi::v1::NodeUnstageVolumeRequest *request,
      csi::v1::NodeUnstageVolumeResponse *response) override
    {
      std::cout << "IdentityService [NodeUnstageVolume]\n";
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "NodeUnstageVolume");
    }

    virtual grpc::Status NodePublishVolume(
      grpc::ServerContext *context,
      const csi::v1::NodePublishVolumeRequest *request,
      csi::v1::NodePublishVolumeResponse *response) override
    {
      std::cout << "IdentityService [NodePublishVolume]\n";
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "NodePublishVolume");
    }

    virtual grpc::Status NodeUnpublishVolume(
      grpc::ServerContext *context,
      const csi::v1::NodeUnpublishVolumeRequest *request,
      csi::v1::NodeUnpublishVolumeResponse *response) override
    {
      std::cout << "IdentityService [NodeUnpublishVolume]\n";
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "NodeUnpublishVolume");
    }

    virtual grpc::Status NodeGetVolumeStats(
      grpc::ServerContext *context,
      const csi::v1::NodeGetVolumeStatsRequest *request,
      csi::v1::NodeGetVolumeStatsResponse *response) override
    {
      std::cout << "IdentityService [NodeGetVolumeStats]\n";
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "NodeGetVolumeStats");
    }

    virtual grpc::Status NodeExpandVolume(
      grpc::ServerContext *context,
      const csi::v1::NodeExpandVolumeRequest *request,
      csi::v1::NodeExpandVolumeResponse *response) override
    {
      std::cout << "IdentityService [NodeExpandVolume]\n";
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "NodeExpandVolume");
    }

    virtual grpc::Status NodeGetCapabilities(
      grpc::ServerContext *context,
      const csi::v1::NodeGetCapabilitiesRequest *request,
      csi::v1::NodeGetCapabilitiesResponse *response) override
    {
      std::cout << "IdentityService [NodeGetCapabilities]\n";
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "NodeGetCapabilities");
    }

    virtual grpc::Status NodeGetInfo(
      grpc::ServerContext *context,
      const csi::v1::NodeGetInfoRequest *request,
      csi::v1::NodeGetInfoResponse *response) override
    {
      std::cout << "IdentityService [NodeGetInfo]\n";
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "NodeGetInfo");
    }
};


#endif