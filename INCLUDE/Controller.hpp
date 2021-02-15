#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <csi.pb.h>
#include <csi.grpc.pb.h>

#include <iostream>

class ControllerService : public csi::v1::Controller::Service
{
  public:

    virtual grpc::Status CreateVolume(
      grpc::ServerContext *context,
      const csi::v1::CreateVolumeRequest *request,
      csi::v1::CreateVolumeResponse *response)
    {
      std::cout << "CreateVolume" << std::endl;
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "CreateVolume");
    }

    virtual grpc::Status DeleteVolume(
      grpc::ServerContext *context,
      const csi::v1::DeleteVolumeRequest *request,
      csi::v1::DeleteVolumeResponse *response)
    {
      std::cout << "DeleteVolume" << std::endl;
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "DeleteVolume");
    }

    virtual grpc::Status ControllerPublishVolume(
      grpc::ServerContext *context,
      const csi::v1::ControllerPublishVolumeRequest *request,
      csi::v1::ControllerPublishVolumeResponse *response)
    {
      std::cout << "ControllerPublishVolume" << std::endl;
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "ControllerPublishVolume");
    }

    virtual grpc::Status ControllerUnpublishVolume(
      grpc::ServerContext *context,
      const csi::v1::ControllerUnpublishVolumeRequest *request,
      csi::v1::ControllerUnpublishVolumeResponse *response)
    {
      std::cout << "ControllerUnpublishVolume" << std::endl;
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "ControllerUnpublishVolume");
    }

    virtual grpc::Status ValidateVolumeCapabilities(
      grpc::ServerContext *context,
      const csi::v1::ValidateVolumeCapabilitiesRequest *request,
      csi::v1::ValidateVolumeCapabilitiesResponse *response)
    {
      std::cout << "ValidateVolumeCapabilities" << std::endl;
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "ValidateVolumeCapabilities");
    }

    virtual grpc::Status ListVolumes(
      grpc::ServerContext *context,
      const csi::v1::ListVolumesRequest *request,
      csi::v1::ListVolumesResponse *response)
    {
      std::cout << "ListVolumes" << std::endl;
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "ListVolumes");
    }

    virtual grpc::Status GetCapacity(
      grpc::ServerContext *context,
      const csi::v1::GetCapacityRequest *request,
      csi::v1::GetCapacityResponse *response)
    {
      std::cout << "GetCapacity" << std::endl;
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "GetCapacity");
    }

    virtual grpc::Status ControllerGetCapabilities(
      grpc::ServerContext *context,
      const csi::v1::ControllerGetCapabilitiesRequest *request,
      csi::v1::ControllerGetCapabilitiesResponse *response)
    {
      std::cout << "ControllerGetCapabilities" << std::endl;

      auto cap = response->add_capabilities();
      cap->mutable_rpc()->set_type(csi::v1::ControllerServiceCapability_RPC_Type::ControllerServiceCapability_RPC_Type_CREATE_DELETE_VOLUME);

      return grpc::Status(grpc::StatusCode::OK, "ControllerGetCapabilities");
    }

    virtual grpc::Status CreateSnapshot(
      grpc::ServerContext *context,
      const csi::v1::CreateSnapshotRequest *request,
      csi::v1::CreateSnapshotResponse *response)
    {
      std::cout << "CreateSnapshot" << std::endl;
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "CreateSnapshot");
    }

    virtual grpc::Status DeleteSnapshot(
      grpc::ServerContext *context,
      const csi::v1::DeleteSnapshotRequest *request, 
      csi::v1::DeleteSnapshotResponse *response)
    {
      std::cout << "DeleteSnapshot" << std::endl;
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "DeleteSnapshot");
    }

    virtual grpc::Status ListSnapshots(
      grpc::ServerContext *context, 
      const csi::v1::ListSnapshotsRequest *request, 
      csi::v1::ListSnapshotsResponse *response)
    {
      std::cout << "ListSnapshots" << std::endl;
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "ListSnapshots");
    }

    virtual grpc::Status ControllerExpandVolume(
      grpc::ServerContext *context, 
      const csi::v1::ControllerExpandVolumeRequest *request, 
      csi::v1::ControllerExpandVolumeResponse *response)
    {
      std::cout << "ControllerExpandVolume" << std::endl;
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "ControllerExpandVolume");
    }

    virtual grpc::Status ControllerGetVolume(
      grpc::ServerContext *context, 
      const csi::v1::ControllerGetVolumeRequest *request, 
      csi::v1::ControllerGetVolumeResponse *response)
    {
      std::cout << "ControllerGetVolume" << std::endl;
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "ControllerGetVolume");
    }
  };
#endif