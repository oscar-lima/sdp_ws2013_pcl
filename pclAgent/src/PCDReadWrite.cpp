/*
 * PCDReadWrite.cpp
 *
 *  Created on: Oct 23, 2013
 *      Author: Oscar Lima
 */


#include "PCDReadWrite.h"

	PCDReadWrite::PCDReadWrite()
	{
		//fileName = defaultFileName;
		PCDReadWrite::fileName = "test_pcd.pcd";
	}

	PCDReadWrite::PCDReadWrite(string providedFileName)
	{
		PCDReadWrite::fileName = providedFileName;
	}

	void PCDReadWrite::read()
	{
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);

		if (pcl::io::loadPCDFile<pcl::PointXYZ> ("../data/pcd_files/"+ fileName, *cloud) == -1) //* load the file
		{
			cout << "Could not read file";
			//PCL_ERROR ("Couldn't read file %s \n", fileName);
		    //return (-1);
		}
		std::cout << "Loaded "
		          << cloud->width * cloud->height
		          << " data points from"+ fileName +" with the following fields: "
		          << std::endl;
		for (size_t i = 0; i < cloud->points.size (); ++i)
			std::cout << "    " << cloud->points[i].x
		              << " "    << cloud->points[i].y
		              << " "    << cloud->points[i].z << std::endl;
	}

	void PCDReadWrite::write(float x, float y, float z)
	{

	}

/*
int main (int argc, char** argv)
{
  PCDReadWrite test;

  test.read();

  return (0);
}

*/
