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
#include "open_ni_viewer.h"

typedef pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud;
string pcd_example = "table.pcd";
string pcd_data_folder = "../../data/pcd_files/";
int sleep_for_x_sec = 0.5;	//helps to do less times the while cicle

static void visualize_pcd(point_cloud cloud);
static string ask_for_file_name();
static point_cloud cloud_to_apply_filter();
PCDSimpleIO cloud_reader;

int main(int argc, char** argv)
{
  int option = 0;
  string file_name = pcd_example;

  cout 	<< "\n::Welcome to pointcloud tester::\n\n"
	<< "Option menu :\n\n"
	<< "1. Load example\n"
	<< "2. Load from file\n"
	<< "3. View from Kinect\n"
	<< "4. Apply downsampling filter\n"
	<< "5. Apply passtrough filter\n\n";
  
  cin >> option;

  point_cloud cloud;
  //pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");
  
  switch(option)
  {
    case 1:
			//cloud = reader.read("../../data/pcd_files/table_scene_lms400.pcd");
			visualize_pcd(cloud_reader.get_cloud(pcd_data_folder + pcd_example));
			break;
    case 2:
			//cloud = reader.read("../../data/pcd_files/kitchen.pcd");
			{
				file_name = ask_for_file_name();
				visualize_pcd(cloud_reader.get_cloud(pcd_data_folder + file_name));
			} break;
		
    case 3:
			{
				SimpleOpenNIViewer kinect;
				kinect.run();
			}
	break;
		
	case 4:		//Downsample
			{
				cloud = cloud_to_apply_filter();
				Filters::downsampling(cloud, cloud, 0.01f, 0.01f, 0.01f);
				visualize_pcd(cloud);
			} break;
	
	case 5:		//Apply passtrough filter
			{
				cout << "Under construction";
			} break;
	
	case 6:		//exit
			{
			
			} break;
    default:
			cout << "\n\nInvalid option\n\n";
			break;
  }
  /*
  while(!viewer.wasStopped()){
    viewer.showCloud(cloud);
    sleep(3);
    Filters::downsampling(cloud, cloud, 0.01f, 0.01f, 0.01f);
  }*/
  //reader.write();
  cout << "End of program";
  return 0;
}

static void visualize_pcd(point_cloud cloud)
{
	pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");
	viewer.showCloud(cloud);
	
	while(!viewer.wasStopped()) sleep(sleep_for_x_sec);
}

static string ask_for_file_name()
{
	string file_name = pcd_example;
	
	cout << "\nPlease enter the file name : ";
	cin >> file_name;
	
	return file_name;
}

static point_cloud cloud_to_apply_filter()
{
	point_cloud cloud;
	
	cloud_reader.get_cloud(pcd_data_folder + ask_for_file_name());
	return cloud;
}
