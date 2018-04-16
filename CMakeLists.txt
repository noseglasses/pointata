project(Pointata)

cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

include_directories("${CMAKE_SOURCE_DIR}/src")

add_subdirectory(src)
add_subdirectory(testing)
