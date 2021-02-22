#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <csi.pb.h>
#include <csi.grpc.pb.h>

#include <DriverFactory.hpp>

#include <string>
#include <iostream>

class ControllerService : public csi::v1::Controller::Service
{
  public:

    virtual grpc::Status CreateVolume(
      grpc::ServerContext *context,
      const csi::v1::CreateVolumeRequest *request,
      csi::v1::CreateVolumeResponse *response)
    {
      std::cout << "ControllerService::CreateVolume" << std::endl;

      SPCBaseDriver driver = nullptr;

      auto& ssname = request->name();
      auto& params = request->parameters();

      grpc::StatusCode fRet = grpc::StatusCode::INVALID_ARGUMENT;

      if (!ssname.size())
      {
        std::cout << "error : storage space name missing" << std::endl;
        goto _end;
      }

      if (params.empty())
      {
        std::cout << "error : parameters empty" << std::endl;
        goto _end;
      }

      fRet = grpc::StatusCode::INTERNAL;

      driver = make_driver(params);

      if (driver)
      {
        auto rc = driver->CreateVolume(ssname, params);

        if (rc)
        {
          std::cout << "driver->CreateVolume successful" << std::endl;
          fRet = grpc::StatusCode::OK;
        }
        else
        {
          std::cout << "driver->CreateVolume failed" << std::endl;
        }
      }

      _end:

      return grpc::Status(fRet, "CreateVolume--");      
    }

    virtual grpc::Status DeleteVolume(
      grpc::ServerContext *context,
      const csi::v1::DeleteVolumeRequest *request,
      csi::v1::DeleteVolumeResponse *response)
    {
      std::cout << "[Controller] DeleteVolume" << std::endl;
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "DeleteVolume");
    }

    virtual grpc::Status ControllerPublishVolume(
      grpc::ServerContext *context,
      const csi::v1::ControllerPublishVolumeRequest *request,
      csi::v1::ControllerPublishVolumeResponse *response)
    {
      std::cout << "[Controller] ControllerPublishVolume" << std::endl;
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "ControllerPublishVolume");
    }

    virtual grpc::Status ControllerUnpublishVolume(
      grpc::ServerContext *context,
      const csi::v1::ControllerUnpublishVolumeRequest *request,
      csi::v1::ControllerUnpublishVolumeResponse *response)
    {
      std::cout << "[Controller] ControllerUnpublishVolume" << std::endl;
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "ControllerUnpublishVolume");
    }

    virtual grpc::Status ValidateVolumeCapabilities(
      grpc::ServerContext *context,
      const csi::v1::ValidateVolumeCapabilitiesRequest *request,
      csi::v1::ValidateVolumeCapabilitiesResponse *response)
    {
      std::cout << "[Controller] ValidateVolumeCapabilities" << std::endl;
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "ValidateVolumeCapabilities");
    }

    virtual grpc::Status ListVolumes(
      grpc::ServerContext *context,
      const csi::v1::ListVolumesRequest *request,
      csi::v1::ListVolumesResponse *response)
    {
      std::cout << "[Controller] ListVolumes" << std::endl;
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "ListVolumes");
    }

    virtual grpc::Status GetCapacity(
      grpc::ServerContext *context,
      const csi::v1::GetCapacityRequest *request,
      csi::v1::GetCapacityResponse *response)
    {
      std::cout << "[Controller] GetCapacity" << std::endl;
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "GetCapacity");
    }

    virtual grpc::Status ControllerGetCapabilities(
      grpc::ServerContext *context,
      const csi::v1::ControllerGetCapabilitiesRequest *request,
      csi::v1::ControllerGetCapabilitiesResponse *response)
    {
      std::cout << "[Controller] ControllerGetCapabilities" << std::endl;

      auto cap1 = response->add_capabilities();
      cap1->mutable_rpc()->set_type(csi::v1::ControllerServiceCapability_RPC_Type::ControllerServiceCapability_RPC_Type_CREATE_DELETE_VOLUME);

      auto cap2= response->add_capabilities();
      cap2->mutable_rpc()->set_type(csi::v1::ControllerServiceCapability_RPC_Type::ControllerServiceCapability_RPC_Type_PUBLISH_UNPUBLISH_VOLUME);

      return grpc::Status(grpc::StatusCode::OK, "ControllerGetCapabilities");
    }

    virtual grpc::Status CreateSnapshot(
      grpc::ServerContext *context,
      const csi::v1::CreateSnapshotRequest *request,
      csi::v1::CreateSnapshotResponse *response)
    {
      std::cout << "[Controller] CreateSnapshot" << std::endl;
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "CreateSnapshot");
    }

    virtual grpc::Status DeleteSnapshot(
      grpc::ServerContext *context,
      const csi::v1::DeleteSnapshotRequest *request, 
      csi::v1::DeleteSnapshotResponse *response)
    {
      std::cout << "[Controller] DeleteSnapshot" << std::endl;
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "DeleteSnapshot");
    }

    virtual grpc::Status ListSnapshots(
      grpc::ServerContext *context, 
      const csi::v1::ListSnapshotsRequest *request, 
      csi::v1::ListSnapshotsResponse *response)
    {
      std::cout << "[Controller] ListSnapshots" << std::endl;
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "ListSnapshots");
    }

    virtual grpc::Status ControllerExpandVolume(
      grpc::ServerContext *context, 
      const csi::v1::ControllerExpandVolumeRequest *request, 
      csi::v1::ControllerExpandVolumeResponse *response)
    {
      std::cout << "[Controller] ControllerExpandVolume" << std::endl;
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "ControllerExpandVolume");
    }

    virtual grpc::Status ControllerGetVolume(
      grpc::ServerContext *context, 
      const csi::v1::ControllerGetVolumeRequest *request, 
      csi::v1::ControllerGetVolumeResponse *response)
    {
      std::cout << "[Controller] ControllerGetVolume" << std::endl;
      return grpc::Status(grpc::StatusCode::UNIMPLEMENTED, "ControllerGetVolume");
    }
  };
#endif