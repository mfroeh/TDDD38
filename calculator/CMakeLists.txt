cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(calculator)
file(GLOB SOURCE_FILES *.cc)
add_executable(calc ${SOURCE_FILES})
