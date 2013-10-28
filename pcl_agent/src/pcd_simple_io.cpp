/*
 * PCDSimpleIO.cpp
 *
 *  Created on: Oct 23, 2013
 *      Author: Oscar Lima
 */

#include "pcd_simple_io.h"

PCDSimpleIO::PCDSimpleIO()
{
	//fileName = defaultFileName;
	PCDSimpleIO::fileName = "test_pcd.pcd";
}

PCDSimpleIO::PCDSimpleIO(string providedFileName)
{
	PCDSimpleIO::fileName = providedFileName;
}

pcl::PointCloud<pcl::PointXYZ>::Ptr PCDSimpleIO::read(string path_and_filename)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);

  //if (pcl::io::loadPCDFile<pcl::PointXYZ> ("../data/pcd_files/"+ fileName, *cloud) == -1) //* load the file
  if (pcl::io::loadPCDFile<pcl::PointXYZ> (path_and_filename, *cloud) == -1) //* load the file
  {
    cout << "Error : Could not read pcd file";
    //PCL_ERROR ("Couldn't read file %s \n", fileName);
    
    pcl::io::loadPCDFile<pcl::PointXYZ> ("../../data/pcd_files/test_pcd.pcd", *cloud); //error, load something
    return cloud;
  }
  
  std::cout << "Loaded "
	    << cloud->width * cloud->height
	    << " data points from"+ fileName +" with the following fields: "
	    << std::endl;

/*
  for (size_t i = 0; i < cloud->points.size (); ++i)
    std::cout << "    " << cloud->points[i].x
	      << " "    << cloud->points[i].y
	      << " "    << cloud->points[i].z << std::endl;
*/

  return cloud;
}

void PCDSimpleIO::write()
{
	pcl::PointCloud<pcl::PointXYZ> cloud;

	// Fill in the cloud data
	cloud.width    = 5;
	cloud.height   = 1;
	cloud.is_dense = false;
	cloud.points.resize (cloud.width * cloud.height);

	for (size_t i = 0; i < cloud.points.size (); ++i)
	{
		cloud.points[i].x = 1024 * rand () / (RAND_MAX + 1.0f);
		cloud.points[i].y = 1024 * rand () / (RAND_MAX + 1.0f);
		cloud.points[i].z = 1024 * rand () / (RAND_MAX + 1.0f);
	}

	pcl::io::savePCDFileASCII ("write_test_pcd.pcd", cloud);
	std::cerr << "Saved " << cloud.points.size () << " data points to test_pcd.pcd." << std::endl;

	for (size_t i = 0; i < cloud.points.size (); ++i)
		std::cerr << "    " << cloud.points[i].x << " " << cloud.points[i].y << " " << cloud.points[i].z << std::endl;
}
