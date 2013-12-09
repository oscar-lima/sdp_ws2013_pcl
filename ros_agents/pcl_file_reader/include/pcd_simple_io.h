/*
 * 	PCL file reader
 *
 *  Created on: Nov 28, 2013
 *  Author: Oscar Lima
 */

#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <cstring>

using namespace std;

class PCDSimpleIO
{
	public:
	
	string file_name;
	string pcd_data_folder;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;

	PCDSimpleIO(string _pcd_data_folder, string _file_name);
	bool getCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud);
	pcl::PointCloud<pcl::PointXYZ>::Ptr getCloud2(bool &success);
	void setFileName(string _file_name);
	string getFileName();
	void SetPcdDataFolder(string _pcd_data_folder);
	string getPcdDataFolder();

};