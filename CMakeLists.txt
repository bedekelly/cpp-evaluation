cmake_minimum_required(VERSION 3.6)
project(Assignment_3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES evalobjmain.cpp evalobj.h evalobj.cpp)
add_executable(Assignment_3 ${SOURCE_FILES} evalobj.h)