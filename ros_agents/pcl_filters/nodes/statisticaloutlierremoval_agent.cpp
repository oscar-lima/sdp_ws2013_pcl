#include <ros/ros.h>
#include "pcl_ros/point_cloud.h"
#include "statisticaloutlierremoval_filter.h"




typedef pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud;
ros::Publisher pub;
statisticaloutlierremovalFilter test;


void cloud_cb(point_cloud src_cloud)
{
	int neighbours = 0;
	double standard_deviation = 0.0f;
	
	ros::param::get("/statisticaloutlierremoval_filter/neighbours", neighbours);
	ros::param::get("/statisticaloutlierremoval_filter/standard_deviation", standard_deviation);
	//point_cloud dest_cloud
	test.setNeighbours(neighbours);
	test.setStandardDeviation(standard_deviation);
	test.applyFilter(src_cloud,src_cloud);
	pub.publish(src_cloud); 
	
}

int main (int argc, char** argv)
{
	// Initialize ROS
	ros::init (argc, argv, "statisticaloutlierremoval_filter");
	ros::NodeHandle nh;
	// Create a ROS subscriber for the input point cloud
	ros::Subscriber sub = nh.subscribe ("/cloud", 1, cloud_cb);

	//Create a ROS publisher for the output point cloud
	pub = nh.advertise<pcl::PointCloud<pcl::PointXYZ> > ("/filtered_cloud", 1);

	ros::spin();
}
