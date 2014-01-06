#include <ros/ros.h>
// PCL specific includes
#include "pcl_ros/point_cloud.h"
#include "kinect_reader.h"

std::string kinect_pub;
ros::Publisher pub;
KinectReader *kinect_live;

int main(int argc, char** argv){
	kinect_live = new KinectReader;
	// Initialize ROS
	ros::init(argc, argv, "pcl_kinect");
	ros::NodeHandle nh("~");
	pub = nh.advertise<pcl::PointCloud<pcl::PointXYZ> >("output_cloud", 1);
	// Spin
	while (kinect_live->isRunning() && ros::ok()){
		ros::spinOnce();
		if (kinect_live->isCloudUnpublished())
			pub.publish(kinect_live->getCloud());
	}
	delete kinect_live;
	return 0;
}
