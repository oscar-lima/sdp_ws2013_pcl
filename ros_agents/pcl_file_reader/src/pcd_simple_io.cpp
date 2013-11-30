/*
 * 	PCL file reader
 *
 *  Created on: Nov 28, 2013
 *  Author: Oscar Lima
 */

#include "pcd_simple_io.h"

PCDSimpleIO::PCDSimpleIO(string _pcd_data_folder, string _file_name)
{
	PCDSimpleIO::pcd_data_folder = _pcd_data_folder;
	PCDSimpleIO::file_name = _file_name;
	PCDSimpleIO::cloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>());
}

bool PCDSimpleIO::getCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud)
{
	if (pcl::io::loadPCDFile<pcl::PointXYZ> (pcd_data_folder + file_name, *cloud) == -1) //* load the file
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
	
	if (pcl::io::loadPCDFile<pcl::PointXYZ> (pcd_data_folder + file_name, *PCDSimpleIO::cloud) == -1) //* load the file
	{
		success = false;
		//Could not read pcd file
		return empty_cloud;
	}
	else
	{
		success = true;
		//Cloud loaded succesfully
		return PCDSimpleIO::cloud;
	}
}

void PCDSimpleIO::setFileName(string _file_name)
{
	PCDSimpleIO::file_name = _file_name;
}

string PCDSimpleIO::getFileName()
{
	return PCDSimpleIO::file_name;
}

void PCDSimpleIO::SetPcdDataFolder(string _pcd_data_folder)
{
	PCDSimpleIO::pcd_data_folder = _pcd_data_folder;
}

string PCDSimpleIO::getPcdDataFolder()
{
	return PCDSimpleIO::pcd_data_folder;
}