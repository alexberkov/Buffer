cmake_minimum_required(VERSION 3.23)
project(Buffer)

set(CMAKE_CXX_STANDARD 20)

add_executable(Buffer main.cpp Buffer.cpp Buffer.h)
add_subdirectory(Server)