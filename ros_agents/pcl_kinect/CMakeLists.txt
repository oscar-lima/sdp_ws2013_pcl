cmake_minimum_required(VERSION 2.8.3)
project(pcl_kinect)

find_package(catkin REQUIRED COMPONENTS 
	roscpp
	dynamic_reconfigure
)

find_package(PCL 1.7 REQUIRED)

generate_dynamic_reconfigure_options(
  cfg/kinect_configure.cfg
)

catkin_package( 
				#INCLUDE_DIRS 
				#LIBRARIES
				CATKIN_DEPENDS
					roscpp
				#DEPENDS
)

include_directories(
  ${catkin_INCLUDE_DIRS}
	${PCL_INCLUDE_DIRS}
	include/
)

add_library(kinect src/kinect_reader.cpp)
add_executable(pcl_kinect nodes/pcl_kinect.cpp)
target_link_libraries(pcl_kinect ${catkin_LIBRARIES} ${PCL_LIBRARIES} kinect)
add_dependencies(pcl_kinect ${PROJECT_NAME}_gencfg)
