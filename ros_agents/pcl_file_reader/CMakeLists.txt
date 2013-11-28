cmake_minimum_required(VERSION 2.8.3)
project(pcl_file_reader)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS 
  roscpp
  sensor_msgs
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
					roscpp message_runtime sensor_msgs pcl_ros #pcl_conversions 
				#DEPENDS
               )

include_directories(
   include/
	${catkin_INCLUDE_DIRS}
	${EIGEN_INCLUDE_DIRS}
	${PCL_INCLUDE_DIRS}
)

add_executable(pcl_file_reader nodes/pcl_file_reader.cpp src/pcd_simple_io.cpp
		)
target_link_libraries(pcl_file_reader ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${EIGEN_LIBRARIES})
