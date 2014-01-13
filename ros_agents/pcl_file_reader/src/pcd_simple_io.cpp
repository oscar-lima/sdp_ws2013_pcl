/*
 * 	PCL file reader
 *
 *  Created on: Nov 28, 2013
 *  Author: Oscar Lima
 */

#include "pcd_simple_io.h"

PCDSimpleIO::PCDSimpleIO(string pcd_data_folder, string file_name)
{
	pcd_data_folder_ = pcd_data_folder;
	file_name_ = file_name;
	cloud_ = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>());
}

bool PCDSimpleIO::getCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud)
{
	if (pcl::io::loadPCDFile<pcl::PointXYZ> (pcd_data_folder_ + file_name_, *cloud) == -1) //* load the file
	{
		//Could not read pcd file
		return false;
	}
	else
	{
		//Cloud loaded succesfully
		return true;
	}
}

pcl::PointCloud<pcl::PointXYZ>::Ptr PCDSimpleIO::getCloud2(bool &success)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr empty_cloud;
	
	if (pcl::io::loadPCDFile<pcl::PointXYZ> (pcd_data_folder_ + file_name_, *cloud_) == -1) //* load the file
	{
		success = false;
		//Could not read pcd file
		return empty_cloud;
	}
	else
	{
		success = true;
		//Cloud loaded succesfully
		return cloud_;
	}
}

void PCDSimpleIO::setFileName(string file_name)
{
	file_name_ = file_name;
}

string PCDSimpleIO::getFileName()
{
	return file_name_;
}

void PCDSimpleIO::SetPcdDataFolder(string pcd_data_folder)
{
	pcd_data_folder_ = pcd_data_folder;
}

string PCDSimpleIO::getPcdDataFolder()
{
	return pcd_data_folder_;
}