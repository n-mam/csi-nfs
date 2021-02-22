#ifndef DRIVERFACTORY_HPP
#define DRIVERFACTORY_HPP

#include <csi.pb.h>
#include <csi.grpc.pb.h>

#include <DriverNFS.hpp>

#include <memory>
#include <string>

auto make_driver(const google::protobuf::Map<std::string, std::string> &params)
{
  std::string type;
  SPCBaseDriver driver;

  try
  {
    type = params.at("driver");
  }
  catch(const std::exception& e)
  {
    std::cout << "make_driver exception : " << e.what() << std::endl;
    return driver;
  }

  if (type == "nfs")
  {
    driver = std::make_shared<CNFSDriver>();
  }
  else if (type == "vhd")
  {

  }
  else
  {
    std::cout << "make_driver unknown driver type" << std::endl;
  }

  return driver;
}

#endif