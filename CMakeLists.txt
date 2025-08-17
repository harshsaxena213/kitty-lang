cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_FLAGS_DEBUG "-g")
project(kitty-lang)

add_executable(meow src/main.cpp)