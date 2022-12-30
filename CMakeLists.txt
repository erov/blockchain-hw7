cmake_minimum_required(VERSION 3.23)
project(hw7)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(SHA256)

add_executable(hw7 main.cpp)

target_include_directories(hw7 PUBLIC sha256)
target_link_libraries(hw7 PUBLIC sha256)

