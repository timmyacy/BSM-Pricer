cmake_minimum_required(VERSION 3.31)
project(BSMPricer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(main
  main.cpp
  src/bsm.cpp
  src/greeks.cpp
  src/ui.cpp
  src/parser.cpp
)
target_include_directories(main PRIVATE include)

add_executable(tests
  tests/bsm_test.cpp
  src/bsm.cpp
  src/greeks.cpp
)
target_include_directories(tests PRIVATE include)
target_link_libraries(tests GTest::gtest_main)
