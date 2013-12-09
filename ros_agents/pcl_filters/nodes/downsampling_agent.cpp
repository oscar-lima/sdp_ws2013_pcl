#include <ros/ros.h>
#include "pcl_ros/point_cloud.h"
#include "downsampling_filter.h"
#include <dynamic_reconfigure/server.h>
#include <pcl_filters/downsamplingConfig.h>

typedef pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud;
ros::Publisher pub;
downsamplingFilter test;
double v_width;
double v_length;
double v_height;

void dynamic_reconfigure_callback(pcl_filters::downsamplingConfig &config, uint32_t level) 
{
	v_width = config.voxel_width;
	v_length = config.voxel_length;
	v_height = config.voxel_height;
	ROS_INFO("Reconfigure Request: %f %f %f",config.voxel_width, config.voxel_length, config.voxel_height);
}

void cloud_cb(point_cloud src_cloud)
{	
	test.setVoxelWidth(v_width);
	test.setVoxelLength(v_length);
	test.setVoxelHeight(v_height);
	test.applyFilter(src_cloud,src_cloud);
	pub.publish(src_cloud); 
}

int main (int argc, char** argv)
{
	// Initialize ROS
	ros::init (argc, argv, "downsampling_filter");
	ros::NodeHandle nh;
	v_width = 0.0f;
	v_length = 0.0f;
	v_height = 0.0f;
	
	dynamic_reconfigure::Server<pcl_filters::downsamplingConfig> server;
	dynamic_reconfigure::Server<pcl_filters::downsamplingConfig>::CallbackType f;
	f = boost::bind(&dynamic_reconfigure_callback, _1, _2);
	server.setCallback(f);
	
	// Create a ROS subscriber for the input point cloud
	ros::Subscriber sub = nh.subscribe ("cloud", 1, cloud_cb);

	//Create a ROS publisher for the output point cloud
	pub = nh.advertise<pcl::PointCloud<pcl::PointXYZ> > ("/cloud", 1);

	ros::spin();
}
