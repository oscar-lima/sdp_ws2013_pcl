cmake_minimum_required(VERSION 2.8.3)
project(pcl_kinect)

find_package(PCL 1.7 REQUIRED)

find_package(catkin REQUIRED COMPONENTS 
	roscpp
)

catkin_package(CATKIN_DEPENDS roscpp)

include_directories(
  ${catkin_INCLUDE_DIRS}
	${PCL_INCLUDE_DIRS}
	include/
)

add_library(kinect src/kinect_reader.cpp)
add_executable(pcl_kinect nodes/pcl_kinect.cpp)

target_link_libraries(kinect
	${PCL_LIBRARIES}
	${catkin_LIBRARIES}
)

target_link_libraries(pcl_kinect
	${catkin_LIBRARIES}
	${PCL_LIBRARIES}
	kinect
)
