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
typedef pcl::PointCloud<pcl::PointXYZ> CloudXYZ;

class PCDSimpleIO
{
	public:
	
	string file_name_;
	string pcd_data_folder_;
	CloudXYZ::Ptr cloud_;

	PCDSimpleIO (string pcd_data_folder, string file_name);
	bool getCloud (CloudXYZ::Ptr &cloud);
	CloudXYZ::Ptr getCloud2 (bool &success);
	void setFileName (string file_name);
	string getFileName ();
	void SetPcdDataFolder (string pcd_data_folder);
	string getPcdDataFolder ();
};