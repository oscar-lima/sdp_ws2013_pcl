cmake_minimum_required(VERSION 2.8.3)
project(dynamic_tutorials)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  dynamic_reconfigure
  driver_base
  roscpp
  rospy
)

generate_dynamic_reconfigure_options(
   #cfg/Tutorials.cfg
    cfg/MyStuff.cfg
)

# make sure configure headers are built before any node using them


include_directories(
	include 
  ${catkin_INCLUDE_DIRS}
)

add_executable(dynamic_reconfigure_node src/dynamic_reconfigure_node.cpp)

 #add_executable(server_node src/server.cpp)
target_link_libraries(dynamic_reconfigure_node ${catkin_LIBRARIES})
add_dependencies(dynamic_reconfigure_node ${PROJECT_NAME}_gencfg) 
 #add_dependencies(server_node ${PROJECT_NAME}_gencfg) 
