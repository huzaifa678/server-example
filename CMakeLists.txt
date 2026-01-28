cmake_minimum_required(VERSION 3.20)
project(server_example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GRPC_HOME /opt/homebrew/opt/grpc)
set(PROTOBUF_HOME /opt/homebrew/opt/protobuf)

find_package(gRPC CONFIG REQUIRED PATHS ${GRPC_HOME}/lib/cmake/grpc)
find_package(Protobuf CONFIG REQUIRED PATHS ${PROTOBUF_HOME}/lib/cmake/protobuf)

file(GLOB SERVER_SRC "servers/*.cpp")
file(GLOB PB_SRC "pb/*.cc")

add_executable(server_example ${SERVER_SRC} ${PB_SRC})

target_include_directories(server_example PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
    ${CMAKE_CURRENT_SOURCE_DIR}/servers
    ${CMAKE_CURRENT_SOURCE_DIR}/pb
    ${Protobuf_INCLUDE_DIRS}      # Protobuf headers
    ${gRPC_INCLUDE_DIRS}          # gRPC headers
)

# Link libraries
target_link_libraries(server_example
    gRPC::grpc++
    protobuf::libprotobuf
    pthread
)
