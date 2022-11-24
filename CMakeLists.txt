cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(child_learn LANGUAGES C CXX)

include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

add_executable(add src/addition.cpp src/translation.cpp)
add_executable(mul src/multiplication.cpp src/translation.cpp)
