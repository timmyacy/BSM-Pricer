cmake_minimum_required(VERSION 3.31)
project(BSMPricer)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(main
  main.cpp
  bsm.cpp
  greeks.cpp
  ui.cpp
)
