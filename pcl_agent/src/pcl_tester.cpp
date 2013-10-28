//Class test section, (uncomment to test)
//#include <boost/thread/thread.hpp>
//#include <pcl/common/common_headers.h>
//#include <pcl/features/normal_3d.h>
//#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
//#include <pcl/console/parse.h>
#include <iostream>
#include <cstdlib>
using namespace std;
#include "pcd_simple_io.h"
//#include "cloud_viewer.h"
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

  cout << "\nSelected option : " << option << "\nEnd of program\n";
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
  pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");
  
  switch(option)
  {
    case 1:
      cloud = reader.read("../../data/pcd_files/table_scene_lms400.pcd");
      break;
    case 2:
      cloud = reader.read("../../data/pcd_files/kitchen.pcd");
      break;
    case 3:
      //TODO get image from kinect image
      break;
    default:
      cout << "Error";
      break;
  }
  
  while(!viewer.wasStopped()){
    viewer.showCloud(cloud);
    sleep(3);
    Filters::filter_Downsampling(cloud, cloud, 0.01f, 0.01f, 0.01f);
  }
  //reader.write();
  return 0;
}
