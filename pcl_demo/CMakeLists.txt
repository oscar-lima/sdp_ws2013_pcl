cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(pcl_tester)

find_package(PCL 1.7 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(pcl_tester src/pcl_tester.cpp src/cloud_viewer.cpp src/pcd_simple_io.cpp src/filters.cpp)
target_link_libraries(pcl_tester ${PCL_LIBRARIES})
