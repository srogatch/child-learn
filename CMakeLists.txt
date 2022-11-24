cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(child_learn LANGUAGES C CXX)

include(CTest)

add_subdirectory(external/fmt)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

include_directories(external/fmt/include)

if(MSVC)
  add_compile_options(/W4 /utf-8)
endif()

add_executable(add src/addition.cpp src/translation.cpp)
target_link_libraries(add fmt::fmt)
add_executable(mul src/multiplication.cpp src/translation.cpp)
target_link_libraries(mul fmt::fmt)
