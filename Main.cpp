#include <Node.hpp>
#include <Identity.hpp>
#include <Controller.hpp>

#include <gflags/gflags.h>
#include <grpcpp/server_builder.h>

#include <iostream>

DEFINE_string(nodeid, "", "CSI nodeid");
DEFINE_bool(controller, false, "Run as controller");
DEFINE_string(endpoint, "0.0.0.0:50051", "gRPC service endpoint");

int main(int argc, char *argv[])
{
  gflags::SetVersionString("1.0.0");
  gflags::SetUsageMessage("MSYS CSI Driver");
  google::ParseCommandLineFlags(&argc, &argv, true);

  std::cout << "--nodeid " << FLAGS_nodeid << std::endl;
  std::cout << "--endpoint " << FLAGS_endpoint << std::endl;
  std::cout << "--controller " << FLAGS_controller << std::endl;

  grpc::ServerBuilder builder;

  builder.AddListeningPort(FLAGS_endpoint, grpc::InsecureServerCredentials());

  ControllerService cs;
  NodeService ns(FLAGS_nodeid);
  IdentityService is(FLAGS_controller);

  builder.RegisterService(&is);
  builder.RegisterService(&ns);
  builder.RegisterService(&cs);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

  std::cout << "server listening ... " << std::endl;

  server->Wait();

  return 0;
}