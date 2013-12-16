#include <ros/ros.h>
// PCL specific includes
#include "pcl_ros/point_cloud.h"
#include "kinect_reader.h"
#include <dynamic_reconfigure/server.h>
#include "pcl_kinect/kinectConfig.h"

std::string kinect_pub;
ros::Publisher pub;
KinectReader *kinect_live;

void reconfigureCallback(pcl_kinect::kinectConfig &config, uint32_t level);
/*
void publisherCallback(CloudXYZ::Ptr cloud){
	viewer->setDisplayedCloud(cloud);
	//ROS_INFO("Cloud received: %lu points", viewer->getDisplayedCloud()->points.size());
}*/

void reconfigureCallback(pcl_kinect::kinectConfig &config, uint32_t level){
	// Create a ROS subscriber for the input point cloud
	ROS_INFO("Topic name received: %s", config.kinect_pub.c_str());
	if (!config.kinect_pub.empty() && !(kinect_pub == config.kinect_pub.c_str())){
		pub.shutdown();
		kinect_pub = config.kinect_pub.c_str();
		ros::NodeHandle nh;
		pub = nh.advertise<pcl::PointCloud<pcl::PointXYZ> >(kinect_pub, 1);
	}
}

int main(int argc, char** argv){
	kinect_live = new KinectReader;
	// Initialize ROS
	ros::init(argc, argv, "pcl_kinect");
	
	dynamic_reconfigure::Server<pcl_kinect::kinectConfig> server;
	dynamic_reconfigure::Server<pcl_kinect::kinectConfig>::CallbackType f;
	
	f = boost::bind(&reconfigureCallback, _1, _2);
	server.setCallback(f);
	
	// Spin
	while (kinect_live->isRunning() && ros::ok()){
		ros::spinOnce();
		if (kinect_live->isCloudUnpublished())
			pub.publish(kinect_live->getCloud());
	}
	delete kinect_live;
	return 0;
}
