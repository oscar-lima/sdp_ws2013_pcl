#include <ros/ros.h>
#include "pcl_ros/point_cloud.h"
#include "downsampling_filter.h"
#include <dynamic_reconfigure/server.h>
#include <pcl_filters/downsamplingConfig.h>

typedef pcl::PointCloud<pcl::PointXYZ>::Ptr CloudXYZ;
ros::Publisher pub_;
ros::Subscriber sub_;
DownsamplingFilter test_;
double v_width_;
double v_length_;
double v_height_;
std::string downsampling_sub_;
std::string downsampling_pub_;

void cloudCallback(CloudXYZ src_cloud);
void dynamicReconfigureCallback(pcl_filters::downsamplingConfig &config, uint32_t level);

void dynamicReconfigureCallback(pcl_filters::downsamplingConfig &config, uint32_t level) 
{
	ros::NodeHandle nh("~");
	if (v_width_ != config.voxel_width)
	{
		v_width_ = config.voxel_width;
	}
	if (v_length_ != config.voxel_length)
	{
		v_length_ = config.voxel_length;
	}
	if (v_height_ != config.voxel_height)
	{
		v_height_ = config.voxel_height;
	}
	std::string temp_str = config.downsampling_sub.c_str();
	if (!config.downsampling_sub.empty() && downsampling_sub_.compare(temp_str) != 0)
	{
		downsampling_sub_ = config.downsampling_sub.c_str();
		sub_.shutdown();
		sub_ = nh.subscribe (downsampling_sub_, 1, cloudCallback);
	}
	ROS_INFO("Reconfigure Request: %f %f %f",v_width_ ,v_length_, v_height_);
}

void cloudCallback(CloudXYZ src_cloud)
{
	test_.setVoxelWidth(v_width_);
	test_.setVoxelLength(v_length_);
	test_.setVoxelHeight(v_height_);
	test_.applyFilter(src_cloud,src_cloud);
	pub_.publish(src_cloud); 
}

int main (int argc, char** argv)
{
	// Initialize ROS
	ros::init (argc, argv, "downsampling_filter");
	ros::NodeHandle nh("~");
	pub_ = nh.advertise<pcl::PointCloud<pcl::PointXYZ> > ("output_cloud", 1);
	v_width_ = 0.0f;
	v_length_ = 0.0f;
	v_height_ = 0.0f;
	dynamic_reconfigure::Server<pcl_filters::downsamplingConfig> server;
	dynamic_reconfigure::Server<pcl_filters::downsamplingConfig>::CallbackType f;
	f = boost::bind(&dynamicReconfigureCallback, _1, _2);
	server.setCallback(f);
	ros::spin();
}
