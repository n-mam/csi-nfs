#include <Node.hpp>
#include <Identity.hpp>
#include <Controller.hpp>

#include <grpcpp/server_builder.h>

#include <iostream>

int main(int argc, char *argv[])
{
  std::cout << std::string(argv[0]) << " " << argc << std::endl;

  bool isController = false;

  if (argc == 3)
  {
    isController = true;
  }

  grpc::ServerBuilder builder;

  builder.AddListeningPort("unix:///csi/csi.sock", grpc::InsecureServerCredentials());

  NodeService ns;
  ControllerService cs;
  IdentityService is(isController);

  builder.RegisterService(&is);
  builder.RegisterService(&ns);
  builder.RegisterService(&cs);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

  std::cout << "Server listening ... " << std::endl;

  server->Wait();

  return 0;
}