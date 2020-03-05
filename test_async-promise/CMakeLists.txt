cmake_minimum_required(VERSION 3.12)
project(test_async_promise)

set(CMAKE_CXX_STANDARD 17)
SET( CMAKE_CXX_FLAGS  "-pthread")

add_executable(test_async_promise main.cpp)