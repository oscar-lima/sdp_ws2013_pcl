/*
 * 	PCL file reader
 *
 *  Created on: Nov 28, 2013
 *  Author: Oscar Lima
 */

#include <ros/ros.h>
#include <sys/stat.h>  //to check file existance
#include <ros/package.h>
#include <dynamic_reconfigure/server.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl_file_reader/pcl_file_readerConfig.h>

#include "pcl_ros/point_cloud.h"
#include "std_msgs/String.h"
#include "pcd_simple_io.h"

ros::Publisher g_cloud_pub;

std::string g_pcd_path;
std::string g_pcd_filename;

void dynamicReconfigureCallback (pcl_file_reader::pcl_file_readerConfig &config, uint32_t level)
{
	bool file_existance = false;
	const std::string& filename = "";

	//ROS_INFO("Reconfigure request received...");

	g_pcd_path = config.g_pcd_path.c_str ();
	g_pcd_filename = config.g_pcd_filename.c_str ();
	
	filename = g_pcd_path + g_pcd_filename;
	
	struct stat buf;
	if (stat (filename.c_str (), &buf) != -1)
	{
		file_existance = true;
	}

	if (g_pcd_path != "" && g_pcd_filename != "" && file_existance == true)
	{
		bool cloud_read_success = false;
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;

		PCDSimpleIO cloud_reader (g_pcd_path, g_pcd_filename);
		cloud = cloud_reader.getCloud2 (cloud_read_success);

		if (cloud_read_success)
		{
			if (cloud->points.size() != 0)
			{
				ROS_INFO ("Cloud succesfully loaded : %lu points", cloud->points.size ());
				g_cloud_pub.publish (cloud);
			}
			else
			{
				ROS_ERROR ("Attempting to publish empty cloud");
			}
		}
		else
		{
			ROS_ERROR ("Could not read pcd file, ensure that pcd_path and pcd_filename parameters have correct values");
		}
	}
}

int main (int argc, char **argv) 
{
	ros::init (argc, argv, "pcl_file_reader");
	ROS_INFO ("pcl_reader node initialized ...");

	ros::NodeHandle nh ("~");
	g_cloud_pub = nh.advertise<pcl::PointCloud<pcl::PointXYZ> > ("output_cloud", 1);
	
	dynamic_reconfigure::Server<pcl_file_reader::pcl_file_readerConfig> reader;
	dynamic_reconfigure::Server<pcl_file_reader::pcl_file_readerConfig>::CallbackType f;

	f = boost::bind (&dynamicReconfigureCallback, _1, _2);
	reader.setCallback (f);

	ros::spin ();
}