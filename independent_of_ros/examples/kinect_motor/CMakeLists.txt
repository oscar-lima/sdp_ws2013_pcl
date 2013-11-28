cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(kinect_motor)

find_package(PCL 1.7.1 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (kinect_motor src/kinect_test.cpp)
target_link_libraries (kinect_motor ${PCL_LIBRARIES})