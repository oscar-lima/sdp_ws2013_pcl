/*
 * PCDSimpleIO.cpp
 *
 *  Created on: Oct 23, 2013
 *      Author: Oscar Lima
 */

#include "pcd_simple_io.h"
using namespace std;

PCDSimpleIO::PCDSimpleIO()
{
	//fileName = ErrorFileName;
	PCDSimpleIO::fileName = "test_pcd.pcd";
}

PCDSimpleIO::PCDSimpleIO(string providedFileName)
{
	PCDSimpleIO::fileName = providedFileName;
}

pcl::PointCloud<pcl::PointXYZ>::Ptr PCDSimpleIO::get_cloud(string path_and_filename)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);

  //if (pcl::io::loadPCDFile<pcl::PointXYZ> ("../data/pcd_files/"+ fileName, *cloud) == -1) //* load the file
  if (pcl::io::loadPCDFile<pcl::PointXYZ> (path_and_filename, *cloud) == -1) //* load the file
  {
    cout << "\nError : Could not read pcd file\nDid you miss to type the .pcd extension?\n\n";
    //PCL_ERROR ("Couldn't read file %s \n", fileName);
    
    pcl::io::loadPCDFile<pcl::PointXYZ> ("../data/pcd_files/test_pcd.pcd", *cloud); //error, load something
    return cloud;
  }
  
  std::cout << "\nLoaded "
			<< cloud->width * cloud->height
			<< " data points from "+ path_and_filename +"\n";

/*
  for (size_t i = 0; i < cloud->points.size (); ++i)
    std::cout << "    " << cloud->points[i].x
	      << " "    << cloud->points[i].y
	      << " "    << cloud->points[i].z << std::endl;
*/

  return cloud;
}

