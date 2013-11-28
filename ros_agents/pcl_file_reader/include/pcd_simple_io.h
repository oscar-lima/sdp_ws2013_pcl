/*
 *  pcd_simple_io.h
 *
 *  Created on: Oct 23, 2013
 *  Author: Oscar Lima
 */

#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <cstring>
#include "pcl_ros/point_cloud.h"
#include <ros/package.h>

using namespace std;

class PCDSimpleIO
{
	public:

	std::string pcd_data_folder;
		
	PCDSimpleIO();
	pcl::PointCloud<pcl::PointXYZ>::Ptr getCloud(string filename);
	//Parameters: data folder, filename
	
	private:

	string fileName;
};