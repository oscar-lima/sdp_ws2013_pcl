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
#include "filters.h"

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
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud = reader.read("../../data/pcd_files/table_scene_lms400.pcd");
  CloudViewer viewer;
  Filters filter;
  filter.filter_Downsampling(cloud, cloud, 0.01f, 0.01f, 0.01f);
  boost::shared_ptr<pcl::visualization::PCLVisualizer> window = viewer.simpleVis(cloud);
  while (!window->wasStopped()) {
    window->spinOnce(100);
    boost::this_thread::sleep(boost::posix_time::microseconds(100000));
  }
  
  //reader.write();
  return 0;
}
