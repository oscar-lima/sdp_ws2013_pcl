/*
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include "cloud_viewer.h"

int main(int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

  if (pcl::io::loadPCDFile<pcl::PointXYZ>("../../data/pcd_files/table_scene_lms400_downsampled.pcd", *cloud) == -1) //* load the file
  {
    PCL_ERROR("Couldn't read pcd file\n");
    return (-1);
  }
  
  std::cout << "Loaded " 
            << cloud->width * cloud->height
            << " data points from test_pcd.pcd with the following fields: "
            << std::endl;
/*
  for (size_t i = 0; i < cloud->points.size(); ++i)
    std::cout << " " << cloud->points[i].x 
              << " " << cloud->points[i].y
              << " " << cloud->points[i].z << std::endl;


  CloudViewer v(cloud);
  return 0;
}
*/
//================================================

//Class test section, (uncomment to test)
//#include <boost/thread/thread.hpp>
//#include <pcl/common/common_headers.h>
//#include <pcl/features/normal_3d.h>
//#include <pcl/io/pcd_io.h>
//#include <pcl/visualization/pcl_visualizer.h>
//#include <pcl/console/parse.h>
#include <iostream>
#include <cstdlib>
using namespace std;

#include "pcd_simple_io.h"
#include "cloud_viewer.h"

int main(int argc, char** argv)
{
  int option = 0;
  PCDSimpleIO reader;


  cout 	<< "Please select one of the following options:\n\n"
	<< "1. Load table image\n"
	<< "2. Load kitchen\n"
	<< "3. Apply downsampling filter\n"
	<< "4. Apply passtrough filter\n\n";
  
  cin >> option;
/*  
  cout << "\nSelected option : " << option << "\nEnd of program\n";
  
  switch(option)
  {
    case 0:	cout << "Not a valid option";
      break;
    case 1:	CloudViewer viewer(reader.read("../../data/pcd_files/table_scene_lms400.pcd"));
      break;
    case 2:	CloudViewer viewer(reader.read("../../data/pcd_files/kitchen.pcd"));
      break;
    case 3:	CloudViewer viewer(reader.read("../../data/pcd_files/table_scene_lms400_downsampled.pcd"));
      break;
    case 4:	cout << "Under construction";
      break;
    default:	cout << "Error";
      break;
  }
  */
  CloudViewer viewer(reader.read("../../data/pcd_files/table_scene_lms400.pcd"));
  CloudViewer viewer2(reader.read("../../data/pcd_files/table_scene_lms400_downsampled.pcd"));
  //reader.write();
  return 0;
}