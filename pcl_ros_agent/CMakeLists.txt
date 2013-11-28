cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(pcl_agent)

find_package(catkin REQUIRED
  COMPONENTS
	roscpp
	roslib
)
add_definitions(-std=gnu++0x)

add_definitions(-Wno-write-strings)

find_package(PCL 1.7 REQUIRED)

catkin_package()

include_directories(
	${catkin_INCLUDE_DIRS}
	${PCL_INCLUDE_DIRS}
	/usr/include/ni/
)

add_executable(pcl_tester 
	src/pcl_tester.cpp src/cloud_viewer.cpp 
	src/pcd_simple_io.cpp src/filters.cpp
)
target_link_libraries(pcl_tester 
	${catkin_LIBRARIES}
	${PCL_LIBRARIES}
)
