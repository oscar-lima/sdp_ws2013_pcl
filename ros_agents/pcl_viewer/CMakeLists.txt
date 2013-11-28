cmake_minimum_required(VERSION 2.8.3)
project(pcl_viewer)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS 
  roscpp
 
  message_generation
  #pcl_conversions 
  pcl_ros
)
find_package(PCL 1.7 REQUIRED)
find_package(Eigen REQUIRED)

catkin_package( 
				#INCLUDE_DIRS 
				#LIBRARIES
				CATKIN_DEPENDS
					roscpp message_runtime pcl_ros #pcl_conversions 
				#DEPENDS
               )

include_directories(
  ${catkin_INCLUDE_DIRS}
  #/opt/ros/hydro/include/
  #/usr/include/pcl-1.7/
   ${EIGEN_INCLUDE_DIRS}
	${PCL_INCLUDE_DIRS}
)

add_executable(pcl_viewer nodes/pcl_viewer.cpp)
target_link_libraries(pcl_viewer ${catkin_LIBRARIES} ${PCL_LIBRARIES})
