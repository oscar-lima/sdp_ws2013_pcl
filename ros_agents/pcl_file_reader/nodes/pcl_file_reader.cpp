#include <ros/ros.h>
#include <pcl_file_reader/pcl_file_readerConfig.h>
#include <dynamic_reconfigure/server.h>
#include <pcl/visualization/cloud_viewer.h>
#include "pcl_ros/point_cloud.h"
#include <ros/package.h>
#include "std_msgs/String.h"

#include "pcd_simple_io.h"

ros::Publisher cloud_pub;
ros::Subscriber sub;

void callback(pcl_file_reader::pcl_file_readerConfig &config, uint32_t level) 
{
  ROS_INFO("Reconfigure Request");
}

void read_request_cb(const std_msgs::String::ConstPtr& pcl_reading_args)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
	std::string _pcd_path, _pcd_filename;
	ros::NodeHandle nh;
	bool cloud_read_succes = false;
	
	ROS_INFO("Point cloud reading request received with the follow arguments : [%s]", pcl_reading_args->data.c_str());
	
	nh.getParam("/pcl_file_reader/pcd_path", _pcd_path);
	nh.getParam("/pcl_file_reader/pcd_filename", _pcd_filename);
	
	ROS_INFO("filename");
	
	PCDSimpleIO cloud_reader(_pcd_path, _pcd_filename);

	cloud = cloud_reader.getCloud2(cloud_read_succes);
	
	if(cloud_read_succes)
	{
		if (cloud->points.size() != 0)
		{
			ROS_INFO("Cloud succesfully loaded : %lu points", cloud->points.size());
			cloud_pub.publish(cloud);
		}
		else
		{
			ROS_ERROR("Attempting to publish empty cloud");
		}
	}
	else
	{
		ROS_ERROR("Could not read pcd file, ensure that /pcd_path and /pcd_filename parameters have correct values");
	}
}

int main(int argc, char **argv) 
{
	ros::init (argc, argv, "pcl_reader");
	ROS_INFO("pcl_reader node initialized ...");
	
  dynamic_reconfigure::Server<pcl_file_reader::pcl_file_readerConfig> reader;
  dynamic_reconfigure::Server<pcl_file_reader::pcl_file_readerConfig>::CallbackType f;

  f = boost::bind(&callback, _1, _2);
  reader.setCallback(f);

	ros::NodeHandle nh;
	
	cloud_pub = nh.advertise<pcl::PointCloud<pcl::PointXYZ> > ("/cloud", 1);
	sub = nh.subscribe("read_request", 1, read_request_cb);
	
	ros::spin();
}