cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_FLAGS "-g -Wall -Werror -std=c++14")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(MAIN_SOURCE_DIR "src")

project(hydraroach)

add_subdirectory(proto)
include_directories(${MAIN_SOURCE_DIR})

add_executable(
  hydraroach
  ${MAIN_SOURCE_DIR}/main.cpp
)

target_link_libraries(hydraroach proto ${PROTOBUF_LIBRARY})
