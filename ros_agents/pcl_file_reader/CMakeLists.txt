cmake_minimum_required(VERSION 2.8.3)
project(pcl_file_reader)

find_package(catkin REQUIRED COMPONENTS 
	roscpp
	rospy
	dynamic_reconfigure
	sensor_msgs
	message_generation 
	pcl_ros
)

find_package(PCL 1.7 REQUIRED)

generate_dynamic_reconfigure_options(cfg/param.cfg)

catkin_package()

include_directories(
   include/
	${catkin_INCLUDE_DIRS}
	${PCL_INCLUDE_DIRS}
)

add_executable(pcl_file_reader nodes/pcl_file_reader.cpp src/pcd_simple_io.cpp)
add_dependencies(pcl_file_reader ${PROJECT_NAME}_gencfg)
target_link_libraries(pcl_file_reader ${catkin_LIBRARIES} ${PCL_LIBRARIES})