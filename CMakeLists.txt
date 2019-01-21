cmake_minimum_required (VERSION 3.8)

project (nbody)

include_directories (phys util test)
file (GLOB_RECURSE SOURCES "*.cpp")

add_executable (nbody ${SOURCES})

message (STATUS ${CMAKE_CXX_FLAGS_DEBUG})