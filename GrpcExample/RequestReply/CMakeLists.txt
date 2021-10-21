# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("RequestReply")

# Find Dependencies
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

# Protobuf stuff
set(PROTO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/protos)
set(PROTOS ${PROTO_PATH}/echoInterface.proto)

set(PROTO_GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${PROTO_GENERATED_DIR})

# cmake modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
include(protobuf)   # includes protobuf helper function (protobuf_generate_cpp)
include(grpc)       # includes grpc helper function (grpc_generate_cpp)

# generate protobuf related files with protoc
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_GENERATED_DIR} ${PROTOS})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_GENERATED_DIR} ${PROTOS})

set(PROTO_GENERATED_FILES
        ${PROTO_SRCS}
        ${PROTO_HDRS}
        ${GRPC_SRCS}
        ${GRPC_HDRS})

# TARGETS
#############################################

# Building server
add_executable(echoServer
        src/server/server.cpp
        ${PROTO_GENERATED_FILES})

target_link_libraries(echoServer
        gRPC::grpc++_reflection
        protobuf::libprotobuf)

target_include_directories(echoServer PUBLIC ${PROTO_GENERATED_DIR})

# Building client
add_executable(echoClient
        src/client/client.cpp
        ${PROTO_GENERATED_FILES})

target_link_libraries(echoClient
        gRPC::grpc++_reflection
        protobuf::libprotobuf)

target_include_directories(echoClient PUBLIC ${PROTO_GENERATED_DIR})
