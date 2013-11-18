cmake_minimum_required(VERSION 2.8.3)
project(pcl_agent)

find_package(catkin REQUIRED COMPONENTS pcl_ros
  roscpp
  sensor_msgs
  message_generation
)
find_package(Eigen REQUIRED)



catkin_package( 
				INCLUDE_DIRS 
					#/opt/ros/hydro/include/
					 ${catkin_INCLUDE_DIRS}
					 /usr/include/pcl-1.7/
					  ${EIGEN_INCLUDE_DIRS}
				#LIBRARIES
				CATKIN_DEPENDS
					roscpp message_runtime sensor_msgs pcl_conversions pcl_ros
				#DEPENDS
               )

###########
## Build ##
###########

include_directories(
  ${catkin_INCLUDE_DIRS}
  #/opt/ros/hydro/include/
  /usr/include/pcl-1.7/
   ${EIGEN_INCLUDE_DIRS}
)

add_executable(pcl_tester src/pcl_tester.cpp)
target_link_libraries(pcl_tester ${catkin_LIBRARIES})
