#include <ros/ros.h>
// PCL specific includes
#include "pcl_ros/point_cloud.h"
#include "displayer.h"

Displayer *viewer;

void viewerCallback(CloudXYZ::Ptr cloud){
	viewer->setDisplayedCloud(cloud);
	//ROS_INFO("Cloud received: %lu points", viewer->getDisplayedCloud()->points.size());
}

int main (int argc, char** argv){
	// Initialize ROS
	viewer = new Displayer();
	ros::init(argc, argv, "pcl_viewer");
	ros::NodeHandle nh;
	// Create a ROS subscriber for the input point cloud
	ros::Subscriber sub = nh.subscribe("/filtered_cloud", 1, viewerCallback);

	// Spin
	while(!viewer->wasStopped() && ros::ok()){
		ros::spinOnce();
	}
	delete(viewer);
}
