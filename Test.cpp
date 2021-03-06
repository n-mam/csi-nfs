#include <grpcpp/grpcpp.h>

#include <csi.pb.h>
#include <csi.grpc.pb.h>

#include <memory>
#include <iostream>

class IdentityClient
{
  public:
   
     IdentityClient(std::shared_ptr<grpc::Channel> channel)
       : iStub(csi::v1::Identity::NewStub(channel))
     {
     }

     void GetPluginInfo(void)
     {
       grpc::ClientContext context;

       csi::v1::GetPluginInfoRequest req;
       csi::v1::GetPluginInfoResponse res;

       auto status = iStub->GetPluginInfo(&context, req, &res);
       
       if (status.ok())
       {
         std::cout << "name : " << res.name() << ", version : " << res.vendor_version() << std::endl;
       }
       else
       {
         std::cout << "GetPluginInfo failed : " << status.error_message() << std::endl;
       }
     }

     void GetPluginCapabilities(void)
     {
       grpc::ClientContext context;

       csi::v1::GetPluginCapabilitiesRequest req;
       csi::v1::GetPluginCapabilitiesResponse res;

       auto status = iStub->GetPluginCapabilities(&context, req, &res);

       if (status.ok())
       {      
         for(auto& cap : res.capabilities())
         {
           std::cout << "capabilities : "
                     << "has_service " << cap.has_service() << ", "
                     << "has_volume_expansion " << cap.has_volume_expansion() << std::endl; 
         }
       }
       else
       {
         std::cout << "Probe failed : " << status.error_message() << std::endl;
       }
     }

     void Probe(void)
     {
       grpc::ClientContext context;

       csi::v1::ProbeRequest req;
       csi::v1::ProbeResponse res;

       auto status = iStub->Probe(&context, req, &res);

       if (status.ok())
       {
         std::cout << "ready : " << res.ready().value() << std::endl;
       }
       else
       {
         std::cout << "Probe failed : " << status.error_message() << std::endl;
       }
     }

  protected:
    
    std::unique_ptr<csi::v1::Identity::Stub> iStub;
};

int main(int argc, char *argv[])
{
  auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());

  IdentityClient idc(channel);

  idc.Probe();
  idc.GetPluginInfo();
  idc.GetPluginCapabilities();

  return 0;
}