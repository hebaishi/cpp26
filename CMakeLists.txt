cmake_minimum_required(VERSION 3.10)
# set(CMAKE_CXX_STANDARD 26)

project(HelloWorld)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++26 -freflection-latest -stdlib=libc++")
set(CMAKE_BUILD_RPATH "$ORIGIN")

add_executable(generate_enum_code generate_enum_code.hpp main.cpp)
