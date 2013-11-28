/*
 * pcd_simple_io.h
 *
 *  Created on: Oct 23, 2013
 *      Author: Oscar Lima
 */

#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <cstring>
#include "pcl_ros/point_cloud.h"

using namespace std;

//#ifndef PCDREADWRITE_H_
//#define PCDREADWRITE_H_

class PCDSimpleIO
{
	public:

	//string fileName;
	//string defaultFileName;

	PCDSimpleIO();
	PCDSimpleIO(string providedFileName);

	//void read();
	pcl::PointCloud<pcl::PointXYZ>::Ptr get_cloud(string path_and_filename);
	
	private:

	string fileName;
};

//#endif /* PCDREADWRITE_H_ */
