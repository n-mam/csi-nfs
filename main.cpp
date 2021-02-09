#include <Node.hpp>
#include <Identity.hpp>

#include <grpcpp/server_builder.h>

#include <iostream>

int main(int argc, char *argv[])
{
  grpc::ServerBuilder builder;

  builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());

  NodeService ns;
  IdentityService is;

  builder.RegisterService(&is);
  builder.RegisterService(&ns);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

  std::cout << "Server listening on " << "0.0.0.0:50051" << "\n";

  server->Wait();

  return 0;
}