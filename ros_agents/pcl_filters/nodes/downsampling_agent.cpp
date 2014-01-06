#include <ros/ros.h>
#include "pcl_ros/point_cloud.h"
#include "downsampling_filter.h"
#include <dynamic_reconfigure/server.h>
#include <pcl_filters/downsamplingConfig.h>

typedef pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud;
ros::Publisher pub;
ros::Subscriber sub;
downsamplingFilter test;
double v_width;
double v_length;
double v_height;
std::string downsampling_sub;
std::string downsampling_pub;

void cloud_cb(point_cloud src_cloud);
void dynamic_reconfigure_callback(pcl_filters::downsamplingConfig &config, uint32_t level);

void dynamic_reconfigure_callback(pcl_filters::downsamplingConfig &config, uint32_t level) 
{	
	ros::NodeHandle nh("~");
	v_width = config.voxel_width;
	v_length = config.voxel_length;
	v_height = config.voxel_height;
	downsampling_sub = config.downsampling_sub.c_str();
	downsampling_pub = config.downsampling_pub.c_str();
	ROS_INFO("Reconfigure Request: %f %f %f",config.voxel_width, config.voxel_length, config.voxel_height);
	sub.shutdown();
	pub.shutdown();
	sub = nh.subscribe (downsampling_sub, 1, cloud_cb);
	pub = nh.advertise<pcl::PointCloud<pcl::PointXYZ> > (downsampling_pub, 1);
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
	v_width = 0.0f;
	v_length = 0.0f;
	v_height = 0.0f;
	dynamic_reconfigure::Server<pcl_filters::downsamplingConfig> server;
	dynamic_reconfigure::Server<pcl_filters::downsamplingConfig>::CallbackType f;
	f = boost::bind(&dynamic_reconfigure_callback, _1, _2);
	server.setCallback(f);
	ros::spin();
}
