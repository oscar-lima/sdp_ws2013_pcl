/*.......................................................
 * Authors: Shehzad Ahmed,Oscar Lima,Iuri Andrade
 * Project:PCL Agentification
*/

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
PCDSimpleIO cloud_reader;

void cloud_ranges_find(point_cloud cloud);
void menu(void);
string ask_for_file_name();

struct range_axis{
	float max_x;
	float min_x;
	float max_y;
	float min_y;
	float max_z;
	float min_z;
}range;


int main(int argc, char** argv)
{
  int option = 0;
  string file_name = pcd_example;
  point_cloud cloud;
  SimpleOpenNIViewer kinect;
  //pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");
 
  cout<< "\n::Welcome to pointcloud tester::\n\n";
  
  while(!kinect.viewer.wasStopped())
  {
	  menu();
	  
	  cin >> option;

	  switch(option)
	  { 
		case 1:
				
				cloud = cloud_reader.get_cloud("../../data/pcd_files/table.pcd");
				//visualize_pcd(cloud);
				kinect.viewer.showCloud(cloud);
				
		break;
		case 2:
				//cloud = reader.read("../../data/pcd_files/kitchen.pcd");
				{
					//file_name = ask_for_file_name();
					cloud = cloud_reader.get_cloud(pcd_data_folder + ask_for_file_name());
					kinect.viewer.showCloud(cloud);
				} 
		break;
			
		case 3:
				{
					//SimpleOpenNIViewer kinect;
					kinect.run();
				}
		break;
			
		case 4:		//Downsample
				{		
					if(cloud == 0)
						cloud = cloud_reader.get_cloud(pcd_data_folder + ask_for_file_name());
						
					Filters::downsampling(cloud, cloud, 0.01f, 0.01f, 0.01f);
					//visualize_pcd(cloud);
					kinect.viewer.showCloud(cloud);
					cout << "\n Cloud filtered.. \n";
				} 
		break;
		
		case 5:		//Apply passtrough filter
					
					
				{	cout << "...........Point Cloud Passthrough Filter process............."<<endl;
					float range_min = 0.0f;
					float range_max = 0.0f;
					char filtration_axis = 'z';
					if(cloud == 0)
						cloud = cloud_reader.get_cloud(pcd_data_folder + ask_for_file_name());
					kinect.viewer.showCloud(cloud);
					cloud_ranges_find(cloud);
					cout << "\nSelect the range & Specify the axis of filtration";
					cout << "\nRange along x-axis:[" << range.min_x << "," << range.max_x<<"]";
					cout << "\nRange along y-axis:[" << range.min_y << "," << range.max_y<<"]";
					cout << "\nRange along z-axis:[" << range.min_z << "," << range.max_z<<"]"<<endl;

					do{
					cout << "\nEnter the axis x, y or z: "; 
					cin >> filtration_axis;
					}while(!(filtration_axis == 'x' || filtration_axis == 'y' || filtration_axis == 'z'));
					
					cout << "\nEnter min. range value: "; 
					cin >> range_min;
					cout << "\nEnter max .range value: "; 
					cin >> range_max;
					
					Filters::passthrough(cloud, cloud, new char(filtration_axis) , range_min, range_max);
					//visualize_pcd(cloud);
					kinect.viewer.showCloud(cloud);
					cout << "\nPoint Cloud is filtered.. \n";
					
				} 
		break;
		
		case 6:		//exit
				{
					cout << "\n\nEnd of program"<<endl;
					kinect.viewer.~CloudViewer();
					return 0;
				} 
		break;
		default:
				cout << "\n\nInvalid option\n\n";
				break;
	}
	option = 0;
  
  
}
  /*
  while(!viewer.wasStopped()){
    viewer.showCloud(cloud);
    sleep(3);
    Filters::downsampling(cloud, cloud, 0.01f, 0.01f, 0.01f);
  }*/
  //reader.write();
  kinect.viewer.~CloudViewer();
  cout << "End of program";
  return 0;
}

string ask_for_file_name(void)
{
	string file_name;
	cout << "\nPlease enter the file name : ";
	cin >> file_name;
	return file_name;
}

void menu(void){

	cout << "Option menu :\n\n"
	<< "1. Load example\n"
	<< "2. Load from file\n"
	<< "3. View from Kinect\n"
	<< "4. Apply downsampling filter\n"
	<< "5. Apply passtrough filter\n"
	<< "6. Exit.\n\n";
}
void cloud_ranges_find(point_cloud cloud){

	 for (size_t i = 0; i < cloud->points.size(); ++i){
		 if(cloud->points[i].x > range.max_x)
		    {range.max_x = cloud->points[i].x;}
		 else if(cloud->points[i].x < range.min_x)
		   { range.min_x = cloud->points[i].x;}
		 if(cloud->points[i].y > range.max_y)
		    {range.max_y = cloud->points[i].y;}
		 else if(cloud->points[i].y < range.min_y)
		   { range.min_y= cloud->points[i].y;}
		 if(cloud->points[i].z > range.max_z)
		    {range.max_z = cloud->points[i].z;}
		 else if(cloud->points[i].z < range.min_z)
		   { range.min_z= cloud->points[i].z;}
		    
		}
}
