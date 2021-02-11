cmake_minimum_required(VERSION 3.0)

project(csi-nfs)

# SET CMAKE_PREFIX_PATH=d:\vcpkg\installed\x64-windows

find_package(gRPC REQUIRED)
find_package(Protobuf REQUIRED)

add_definitions(-D _WIN32_WINNT=0x0600)

# Protbuf generated

set(VCPKG_ROOT D:/vcpkg/installed/x64-windows)
set(PROTOC ${VCPKG_ROOT}/tools/protobuf/protoc.exe)

add_custom_command(
  OUTPUT csi.pb.cc
  COMMAND ${PROTOC} --cpp_out=${CMAKE_SOURCE_DIR}/build -I=${CMAKE_SOURCE_DIR} -I=${VCPKG_ROOT}/include ${CMAKE_SOURCE_DIR}/csi.proto
)

add_custom_command(
  OUTPUT csi.grpc.pb.cc
  COMMAND ${PROTOC} --grpc_out=${CMAKE_SOURCE_DIR}/build --plugin=protoc-gen-grpc="${VCPKG_ROOT}/tools/grpc/grpc_cpp_plugin.exe" -I=${CMAKE_SOURCE_DIR} -I=${VCPKG_ROOT}/include ${CMAKE_SOURCE_DIR}/csi.proto
)

# Main server

add_executable(
  server
  ${CMAKE_SOURCE_DIR}/Main.cpp
  csi.pb.cc
  csi.grpc.pb.cc
)

target_include_directories(
  server
  PRIVATE
  ${CMAKE_SOURCE_DIR}/INCLUDE
  ${CMAKE_SOURCE_DIR}/build
)

target_link_libraries(server Ws2_32.lib)

# Test client

add_executable(
  Test
  ${CMAKE_SOURCE_DIR}/test.cpp
  csi.pb.cc
  csi.grpc.pb.cc
)

target_include_directories(
  Test
  PRIVATE
  ${CMAKE_SOURCE_DIR}/INCLUDE
  ${CMAKE_SOURCE_DIR}/build
)

target_link_libraries(Test Ws2_32.lib)

if (WIN32)
  SET (CMAKE_CXX_FLAGS_RELEASE "/Zi /Od")
  SET_TARGET_PROPERTIES(
   server PROPERTIES LINK_FLAGS 
   "/DEBUG /OPT:REF /OPT:ICF"
  )
endif (WIN32)

if (WIN32)
  SET (CMAKE_CXX_FLAGS_RELEASE "/Zi /Od")
  SET_TARGET_PROPERTIES(
   Test PROPERTIES LINK_FLAGS 
   "/DEBUG /OPT:REF /OPT:ICF"
  )
endif (WIN32)