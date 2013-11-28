/*
 * PCDSimpleIO.cpp
 *
 *  Created on: Oct 23, 2013
 *  Author: Oscar Lima
 */

#include "pcd_simple_io.h"

using namespace std;

PCDSimpleIO::PCDSimpleIO()
{
	PCDSimpleIO::fileName = "test_pcd.pcd";
}

pcl::PointCloud<pcl::PointXYZ>::Ptr PCDSimpleIO::getCloud(string filename)
{
	pcd_data_folder = ros::package::getPath("pcl_file_reader") + "/../../data/pcd_files/";
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);

	if (pcl::io::loadPCDFile<pcl::PointXYZ> (pcd_data_folder + filename, *cloud) == -1) //* load the file
	{
		ROS_ERROR("Could not read pcd file");

		return cloud;
	}

	ROS_INFO("Cloud loaded succesfully");

	return cloud;
}

