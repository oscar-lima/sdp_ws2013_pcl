#include <ros/ros.h>
// PCL specific includes
#include "pcl_ros/point_cloud.h"
#include "kinect_reader.h"

std::string kinect_pub_;
ros::Publisher pub_;
KinectReader *kinect_live_;

int main(int argc, char** argv)
{
	kinect_live_ = new KinectReader;
	// Initialize ROS
	ros::init(argc, argv, "pcl_kinect");
	ros::NodeHandle nh("~");
	pub_ = nh.advertise<pcl::PointCloud<pcl::PointXYZ> >("output_cloud", 1);
	// Spin
	while (kinect_live_->isRunning() && ros::ok())
	{
		ros::spinOnce();
		if (kinect_live_->isCloudUnpublished())
		{
			pub_.publish(kinect_live_->getCloud());
		}
	}
	delete kinect_live_;
	return 0;
}
