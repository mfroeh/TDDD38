cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(linked_list)
file(GLOB SOURCE_FILES *.cc)
add_executable(list ${SOURCE_FILES})
