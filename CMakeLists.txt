cmake_minimum_required(VERSION 3.0.0)
project(circular_buffer_1 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent) 
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  circular_buffer_1
  tests.cpp
)

add_subdirectory(circular_buffer)

target_include_directories(circular_buffer_1 PRIVATE circular_buffer)


target_link_libraries(
  circular_buffer_1 PRIVATE 
  circular_buffer_t
  GTest::gtest_main
)




