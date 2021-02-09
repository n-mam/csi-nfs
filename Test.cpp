#include <csi.pb.h>
#include <csi.grpc.pb.h>

#include <grpcpp/grpcpp.h>

#include <memory>
#include <iostream>

class IdentityClient
{
  public:
   
     IdentityClient(std::shared_ptr<grpc_impl::Channel> channel)
       : iStub(csi::v1::Identity::NewStub(channel))
     {
     }

     void Probe()
     {
       grpc::ClientContext context;

       csi::v1::ProbeRequest req;
       csi::v1::ProbeResponse res;

       auto status = iStub->Probe(&context, req, &res);

       if (status.ok())
       {
         std::cout << "ready : " << res.ready().value() << "\n";
       }
       else
       {
         std::cout << "Probe failed : " << status.error_message() << "\n";
       }
     }

     void GetPluginInfo(void)
     {
       grpc::ClientContext context;

       csi::v1::GetPluginInfoRequest req;
       csi::v1::GetPluginInfoResponse res;

       auto status = iStub->GetPluginInfo(&context, req, &res);
       
       if (status.ok())
       {
         std::cout << "name : " << res.name() << ", version : " << res.vendor_version() << "\n";
       }
       else
       {
         std::cout << "GetPluginInfo failed : " << status.error_message() << "\n";
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

  return 0;
}