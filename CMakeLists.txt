cmake_minimum_required(VERSION 3.31)
project(New)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(New main.cpp add.cpp)

# Force consistent binary name
set_target_properties(New PROPERTIES OUTPUT_NAME "app")
