/*
 * PCDReadWrite.h
 *
 *  Created on: Oct 23, 2013
 *      Author: oscar
 */

#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <cstring>
using namespace std;

#ifndef PCDREADWRITE_H_
#define PCDREADWRITE_H_

class PCDReadWrite
{
	public:

	//string fileName;
	//string defaultFileName;

	PCDReadWrite();
	PCDReadWrite(string providedFileName);

	void read();
	void write();

	private:

	string fileName;
};

#endif /* PCDREADWRITE_H_ */
