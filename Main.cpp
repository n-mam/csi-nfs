#include <Node.hpp>
#include <Identity.hpp>
#include <Controller.hpp>

#include <grpcpp/server_builder.h>

#include <iostream>

int main(int argc, char *argv[])
{
  for (int i = 0; i < argc; i++)
  {
    std::cout << argv[i] << std::endl;
  }

  bool isController = false;

  if (argc == 2)
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

  std::cout << "server listening ... " << std::endl;

  server->Wait();

  return 0;
}