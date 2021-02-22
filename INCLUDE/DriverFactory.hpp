#ifndef DRIVERFACTORY_HPP
#define DRIVERFACTORY_HPP

#include <csi.pb.h>
#include <csi.grpc.pb.h>

#include <DriverNFS.hpp>

#include <memory>
#include <string>

auto make_driver(const std::string& type)
{
  SPCBaseDriver driver;

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