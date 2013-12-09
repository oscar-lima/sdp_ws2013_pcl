#include <ros/ros.h>
#include "pcl_ros/point_cloud.h"
#include "passthrough_filter.h"
#include <pcl/visualization/cloud_viewer.h>
typedef pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud;
ros::Publisher pub;
passthroughFilter test;


void cloud_cb(point_cloud src_cloud)
{
	//point_cloud dest_cloud
	std::string axis;
	double min_range = 0.0f;
	double max_range = 0.0f;
	
	test.cloud_ranges_find(src_cloud);
	ros::param::get("/passthrough_filter/filteration_axis", axis);
	ros::param::get("/passthrough_filter/min_range", min_range);
	ros::param::get("/passthrough_filter/max_range", max_range);
	
	test.setFilterAxis(axis);
	test.setMinRange(min_range);
	test.setMaxRange(max_range);
	test.applyFilter(src_cloud,src_cloud);
	pub.publish(src_cloud); 
	
	pub.shutdown();
}

int main (int argc, char** argv)
{
	// Initialize ROS
	ros::init (argc, argv, "passthrough_filter");
	ros::NodeHandle nh;
	// Create a ROS subscriber for the input point cloud
	ros::Subscriber sub = nh.subscribe ("/cloud", 1, cloud_cb);

	//Create a ROS publisher for the output point cloud
	pub = nh.advertise<pcl::PointCloud<pcl::PointXYZ> > ("/filtered_cloud", 1);

	ros::spin();
}
