/*
 * 	PCL file reader node
 *
 *  Created on: Nov 28, 2013
 *  Author: Oscar Lima
 */

#include <ros/ros.h>
#include <pcl/visualization/cloud_viewer.h>
#include "pcd_simple_io.h"
#include "pcl_ros/point_cloud.h"
#include <ros/package.h>
#include "std_msgs/String.h"

ros::Publisher cloud_pub;
ros::Subscriber sub;

void read_request_cb(const std_msgs::String::ConstPtr& pcl_reading_args)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
	std::string _pcd_path, _pcd_filename;
	ros::NodeHandle nh;
	bool cloud_read_succes = false;
	
	ROS_INFO("Point cloud reading request received with the follow arguments : [%s]", pcl_reading_args->data.c_str());
	
	nh.getParam("/pcl_file_reader/pcd_path", _pcd_path);
	nh.getParam("/pcl_file_reader/pcd_filename", _pcd_filename);
	PCDSimpleIO cloud_reader(_pcd_path, _pcd_filename);
	
	//if(cloud_reader.getCloud(cloud)) //this is more suitable way to do it but it gives runtime error
	cloud = cloud_reader.getCloud2(cloud_read_succes); //instead we are using this way
	
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

int main (int argc, char** argv)
{
	ros::init (argc, argv, "pcl_reader");
	ROS_INFO("pcl_reader node initialized ...");
	
	ros::NodeHandle nh;
		
	if(!nh.hasParam("pcl_file_reader/pcd_filename"))
	{
		nh.setParam("pcl_file_reader/pcd_filename", "table.pcd");
		ROS_INFO("Could not find parameter /pcl_file_reader/pcd_filename , setted to default value by the node");
	}
	
	if(!nh.hasParam("pcl_file_reader/pcd_path"))
	{
		nh.setParam("pcl_file_reader/pcd_path", ros::package::getPath("pcl_file_reader") + "/../../data/pcd_files/");
		ROS_INFO("Could not find parameter /pcl_file_reader/pcd_path , setted to default value by the node");
	}
		
	cloud_pub = nh.advertise<pcl::PointCloud<pcl::PointXYZ> > ("/cloud", 1);
	sub = nh.subscribe("read_request", 1, read_request_cb);
	
	ros::spin();
}
