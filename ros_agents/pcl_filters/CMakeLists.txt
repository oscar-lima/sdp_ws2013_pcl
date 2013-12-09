cmake_minimum_required(VERSION 2.8.3)
project(pcl_filters)
find_package(catkin REQUIRED COMPONENTS 
	roscpp
	rospy
	dynamic_reconfigure
)
find_package(PCL 1.7 REQUIRED)

generate_dynamic_reconfigure_options(
	cfg/downsampling_configure.cfg
	cfg/passthrough_configure.cfg
	cfg/radiusoutlierremoval_configure.cfg
	cfg/statisticaloutlierremoval_configure.cfg
)

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

add_executable(passthrough_filter nodes/passthrough_agent.cpp src/passthrough_filter.cpp)
add_dependencies(passthrough_filter ${PROJECT_NAME}_gencfg)
target_link_libraries(passthrough_filter ${catkin_LIBRARIES} ${PCL_LIBRARIES})

add_executable(downsampling_filter nodes/downsampling_agent.cpp src/downsampling_filter.cpp)
add_dependencies(downsampling_filter ${PROJECT_NAME}_gencfg)
target_link_libraries(downsampling_filter ${catkin_LIBRARIES} ${PCL_LIBRARIES})

add_executable(statisticaloutlierremoval_filter nodes/statisticaloutlierremoval_agent.cpp src/statisticaloutlierremoval_filter.cpp)
add_dependencies(statisticaloutlierremoval_filter ${PROJECT_NAME}_gencfg)
target_link_libraries(statisticaloutlierremoval_filter ${catkin_LIBRARIES} ${PCL_LIBRARIES})

add_executable(radiusoutlierremoval_filter nodes/radiusoutlierremoval_agent.cpp src/radiusoutlierremoval_filter.cpp)
add_dependencies(radiusoutlierremoval_filter ${PROJECT_NAME}_gencfg)
target_link_libraries(radiusoutlierremoval_filter ${catkin_LIBRARIES} ${PCL_LIBRARIES})


