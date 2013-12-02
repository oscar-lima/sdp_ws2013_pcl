#include <ros/ros.h>
#include "pcl_ros/point_cloud.h"
#include "radiusoutlierremoval_filter.h"

typedef pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud;
ros::Publisher pub;
radiusoutlierremovalFilter test;


void cloud_cb(point_cloud src_cloud)
{
	
	test.setMinNeighbours(50);
	test.setSearchRadius(0.6);
	test.applyFilter(src_cloud,src_cloud);
	pub.publish(src_cloud); 
	
}

int main (int argc, char** argv)
{
	// Initialize ROS
	ros::init (argc, argv, "radiusoutlierremoval_filter");
	ros::NodeHandle nh;
	// Create a ROS subscriber for the input point cloud
	ros::Subscriber sub = nh.subscribe ("/cloud", 1, cloud_cb);

	//Create a ROS publisher for the output point cloud
	pub = nh.advertise<pcl::PointCloud<pcl::PointXYZ> > ("/filtered_cloud", 1);

	ros::spin();
}
