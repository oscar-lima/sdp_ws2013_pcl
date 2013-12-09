cmake_minimum_required(VERSION 2.8.3)
project(pcl_viewer)
find_package(catkin REQUIRED COMPONENTS 
	roscpp
)
find_package(PCL 1.7 REQUIRED)
find_package(Eigen REQUIRED)

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
add_library(displayer src/displayer.cpp)
add_executable(pcl_viewer nodes/pcl_viewer.cpp)
target_link_libraries(pcl_viewer ${catkin_LIBRARIES} ${PCL_LIBRARIES} displayer)
