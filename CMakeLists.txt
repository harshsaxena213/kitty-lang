set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Optional: disables compiler-specific extensions, uses -std=c++20


cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_FLAGS_DEBUG "-g")
project(kitty-lang)

add_executable(meow src/main.cpp)

set(CMAKE_CXX_STANDARD 20)