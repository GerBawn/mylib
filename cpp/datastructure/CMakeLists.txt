cmake_minimum_required(VERSION 3.5)
project(datastructure)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(List)
include_directories(List)

#set(SOURCE_FILES main.cpp)
aux_source_directory(. SOURCE_FILES)
add_executable(datastructure ${SOURCE_FILES})
target_link_libraries(datastructure List)