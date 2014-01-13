#include <ros/ros.h>
// PCL specific includes
#include "pcl_ros/point_cloud.h"
#include "displayer.h"
#include <dynamic_reconfigure/server.h>
#include "pcl_viewer/viewerConfig.h"

Displayer *viewer_;
std::string viewer_sub_;
ros::Subscriber subs_;

void reconfigureCallback(pcl_viewer::viewerConfig &config);

void viewerCallback(const CloudXYZ::ConstPtr &cloud)
{
	viewer_->setDisplayedCloud(cloud);
	//ROS_INFO("Cloud received: %lu points", viewer_->getDisplayedCloud()->points.size());
}

void reconfigureCallback(pcl_viewer::viewerConfig &config, uint32_t level)
{
	// Create a ROS subscriber for the input point cloud
	if (!config.viewer_sub.empty() && !(viewer_sub_ == config.viewer_sub.c_str()))
	{
		ROS_INFO("Changing subscriber to: %s", config.viewer_sub.c_str());
		subs_.shutdown();
		viewer_sub_ = config.viewer_sub.c_str();
		ros::NodeHandle nh("~");
		subs_ = nh.subscribe(viewer_sub_, 1, viewerCallback);
	}
}

int main(int argc, char** argv)
{
	// Initialize ROS
	viewer_ = new Displayer;
	ros::init(argc, argv, "pcl_viewer");
	dynamic_reconfigure::Server<pcl_viewer::viewerConfig> server;
	dynamic_reconfigure::Server<pcl_viewer::viewerConfig>::CallbackType f;
	f = boost::bind(&reconfigureCallback, _1, _2);
	server.setCallback(f);
	// Spin
	while (!viewer_->wasStopped() && ros::ok())
	{
		ros::spinOnce();
	}
	delete viewer_;
	return 0;
}
