cmake_minimum_required(VERSION 3.0)

project(csi-nfs)

# SET CMAKE_PREFIX_PATH=d:\vcpkg\installed\x64-windows
# export CMAKE_PREFIX_PATH=~/vcpkg/installed/x64-linux/

find_package(gRPC REQUIRED)
find_package(Protobuf REQUIRED)

# Protbuf generated

if (WIN32)
  add_definitions(-D _WIN32_WINNT=0x0600)
  SET(VCPKG_ROOT D:/vcpkg/installed/x64-windows)
  SET(PROTOC ${VCPKG_ROOT}/tools/protobuf/protoc.exe)
  SET(GRPC_PLUGIN ${VCPKG_ROOT}/tools/grpc/grpc_cpp_plugin.exe)
else()
  SET(VCPKG_ROOT /home/nmam/vcpkg/installed/x64-linux)
  SET(PROTOC /home/nmam/vcpkg/installed/x64-linux/tools/protobuf/protoc)
  SET(GRPC_PLUGIN /home/nmam/vcpkg/installed/x64-linux/tools/grpc/grpc_cpp_plugin)
endif (WIN32)

add_custom_command(
  OUTPUT csi.pb.cc
  COMMAND ${PROTOC} --cpp_out=${CMAKE_SOURCE_DIR}/build -I=${CMAKE_SOURCE_DIR} -I=${VCPKG_ROOT}/include ${CMAKE_SOURCE_DIR}/csi.proto
)

add_custom_command(
  OUTPUT csi.grpc.pb.cc
  COMMAND ${PROTOC} --grpc_out=${CMAKE_SOURCE_DIR}/build --plugin=protoc-gen-grpc="${GRPC_PLUGIN}" -I=${CMAKE_SOURCE_DIR} -I=${VCPKG_ROOT}/include ${CMAKE_SOURCE_DIR}/csi.proto
)

# Main server

add_executable(
  server
  ${CMAKE_SOURCE_DIR}/Main.cpp
  csi.pb.cc
  csi.grpc.pb.cc
)

SET_PROPERTY(TARGET server PROPERTY CXX_STANDARD 17)

target_include_directories(
  server
  PRIVATE
  ${VCPKG_ROOT}/include
  ${CMAKE_SOURCE_DIR}/INCLUDE
  ${CMAKE_SOURCE_DIR}/build
)

# Test client

add_executable(
  Test
  ${CMAKE_SOURCE_DIR}/Test.cpp
  csi.pb.cc
  csi.grpc.pb.cc
)

SET_PROPERTY(TARGET Test PROPERTY CXX_STANDARD 17)

target_include_directories(
  Test
  PRIVATE
  ${VCPKG_ROOT}/include
  ${CMAKE_SOURCE_DIR}/INCLUDE
  ${CMAKE_SOURCE_DIR}/build
)

if (WIN32)
  target_link_libraries(server Ws2_32.lib)
  target_link_libraries(Test Ws2_32.lib)
else()
  target_link_libraries(server PRIVATE gRPC::gpr gRPC::grpc gRPC::grpc++ gRPC::grpc++_alts)
  target_link_libraries(Test PRIVATE gRPC::gpr gRPC::grpc gRPC::grpc++ gRPC::grpc++_alts)
endif (WIN32)

if (WIN32)
  SET (CMAKE_CXX_FLAGS_RELEASE "/Zi /Od")
  SET_TARGET_PROPERTIES(
   server PROPERTIES LINK_FLAGS 
   "/DEBUG /OPT:REF /OPT:ICF"
  )
  SET_TARGET_PROPERTIES(
   Test PROPERTIES LINK_FLAGS 
   "/DEBUG /OPT:REF /OPT:ICF"
  )
endif (WIN32)