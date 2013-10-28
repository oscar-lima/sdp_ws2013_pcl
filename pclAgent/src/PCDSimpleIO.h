/*
 * PCDSimpleIO.h
 *
 *  Created on: Oct 23, 2013
 *      Author: oscar
 */

#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <cstring>
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
	pcl::PointCloud<pcl::PointXYZ>::Ptr read(string path_and_filename);
	void write();

	private:

	string fileName;
};

//#endif /* PCDREADWRITE_H_ */
