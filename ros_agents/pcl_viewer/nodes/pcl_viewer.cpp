#include <ros/ros.h>
// PCL specific includes
#include "pcl_ros/point_cloud.h"
#include "displayer.h"
#include <dynamic_reconfigure/server.h>
#include "pcl_viewer/ViewerConfig.h"

Displayer *viewer;
std::string viewer_sub;
ros::Subscriber subs;

void reconfigureCallback(pcl_viewer::ViewerConfig &config);

void viewerCallback(CloudXYZ::Ptr cloud){
	viewer->setDisplayedCloud(cloud);
	//ROS_INFO("Cloud received: %lu points", viewer->getDisplayedCloud()->points.size());
}

void reconfigureCallback(pcl_viewer::ViewerConfig &config, uint32_t level){
	// Create a ROS subscriber for the input point cloud
	ROS_INFO("Topic name received: %s", config.viewer_sub.c_str());
	if (!config.viewer_sub.empty() && !(viewer_sub == config.viewer_sub.c_str())){
		subs.shutdown();
		viewer_sub = config.viewer_sub.c_str();
		ros::NodeHandle nh;
		subs = nh.subscribe(viewer_sub, 1, viewerCallback);
	}
}

int main(int argc, char** argv){
	// Initialize ROS
	viewer = new Displayer;
	ros::init(argc, argv, "pcl_viewer");
	
	dynamic_reconfigure::Server<pcl_viewer::ViewerConfig> server;
	dynamic_reconfigure::Server<pcl_viewer::ViewerConfig>::CallbackType f;
	
	f = boost::bind(&reconfigureCallback, _1, _2);
	server.setCallback(f);
	
	// Spin
	while (!viewer->wasStopped() && ros::ok()){
		ros::spinOnce();
	}
	delete viewer;
	return 0;
}
