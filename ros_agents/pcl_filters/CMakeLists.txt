cmake_minimum_required(VERSION 2.8.3)
project(pcl_filters)
find_package(catkin REQUIRED COMPONENTS 
  roscpp
)
find_package(PCL 1.7 REQUIRED)

catkin_package( 
				#INCLUDE_DIRS 
				#LIBRARIES
				CATKIN_DEPENDS
					roscpp 
				#DEPENDS
               )
include_directories(
   include/
  ${catkin_INCLUDE_DIRS}
   ${PCL_INCLUDE_DIRS}
)

add_executable(filter_passthrough nodes/passthrough_agent.cpp src/passthrough_filter.cpp)
target_link_libraries(filter_passthrough ${catkin_LIBRARIES} ${PCL_LIBRARIES})

add_executable(filter_downsampling nodes/downsampling_agent.cpp src/downsampling_filter.cpp)
target_link_libraries(filter_downsampling ${catkin_LIBRARIES} ${PCL_LIBRARIES})
