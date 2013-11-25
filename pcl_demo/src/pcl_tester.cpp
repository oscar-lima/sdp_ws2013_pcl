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
#include <pcl/io/openni_grabber.h>


typedef pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud;
string pcd_example = "table.pcd";
string pcd_data_folder = "../../data/pcd_files/";
int sleep_for_x_sec = 0.5;	//helps to do less times the while cicle
PCDSimpleIO cloud_reader;
pcl::visualization::CloudViewer viewer("Cloud Viewer");

void cloud_ranges_find(point_cloud cloud);
void menu(void);
string ask_for_file_name();
void cloud_cb_(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &cloud);

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
  char option = 0;
  string file_name = pcd_example;
  point_cloud cloud;
  
  cout<< "\n::Welcome to pointcloud tester::\n\n";
  
  while(!viewer.wasStopped())
  {
	  menu();
	  
	  cin >> option;

	  switch(option)
	  { 
		case '1':
				{
					cloud = cloud_reader.get_cloud("../../data/pcd_files/table.pcd");
				}
		break;
		case '2':
				{
					cloud = cloud_reader.get_cloud(pcd_data_folder + ask_for_file_name());
				} 
		break;
			
		case '3':
				{
					pcl::Grabber* interface = new pcl::OpenNIGrabber();

					boost::function<void(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr&)> f =
											boost::bind(&cloud_cb_, _1);

					interface->registerCallback(f);

					interface->start();
					
					option = 0;
				}
		break;
			
		case '4':	/*Apply downsampling:
					 *To apply this filter,width(x),length(y) and height(z) of 3D voxel grid(set of tiny 3D boxes in space) is required
				 	 */ 
				{	
					float voxel_grid_size_x = 0.0f;
					float voxel_grid_size_y = 0.0f;
					float voxel_grid_size_z = 0.0f;
						
					if(cloud == 0)
						cloud = cloud_reader.get_cloud(pcd_data_folder + ask_for_file_name());
						
					cout << "\nEnter Voxel grid width(x): "; 
					cin >> voxel_grid_size_x;
					cout << "\nEnter Voxel_grid length(y): "; 
					cin >> voxel_grid_size_y;
					cout << "\nEnter Voxel grid height(z): "; 
					cin >> voxel_grid_size_z;
						
					Filters::downsampling(cloud, cloud, voxel_grid_size_x, voxel_grid_size_x, voxel_grid_size_x);
					cout << "\n Cloud filtered.. \n";
				} 
		break;
		
		case '5':	
					/*Apply passtrough filter:
					 *To apply this filter,select axis of filteration and range to be sliced along the specified axis.
				 	 */ 			
				{	
					float range_min = 0.0f;
					float range_max = 0.0f;
					char filtration_axis[1];
					
					if(cloud == 0)
						cloud = cloud_reader.get_cloud(pcd_data_folder + ask_for_file_name());
					
					viewer.showCloud(cloud);
					cloud_ranges_find(cloud);
					

					do{
					cout << "\nEnter the axis x, y or z: "; 
					cin >> filtration_axis;
					}while(!(filtration_axis[0] == 'x' || filtration_axis[0] == 'y' || filtration_axis[0] == 'z'));
					
					const char *filtration_axis_ptr;
					filtration_axis_ptr = filtration_axis;
					
					cout << "\nEnter min. range value: "; 
					cin >> range_min;
					cout << "\nEnter max .range value: "; 
					cin >> range_max;
					
					Filters::passthrough(cloud, cloud, filtration_axis_ptr , range_min, range_max);
					cout << "\nPoint Cloud is filtered.. \n";
					
				} 
		break;
		case '6':	/*Apply Statistical outlier filter:
				 	*To apply this filter,number of neighobors to consider for Mean distance and standard deviation
				 	* from mean distance is required
				 	*/ 
				{
					int MinNeighborsforMeanDistance = 0;
					float StandardDeviationfromMeanDistance = 0.0f;
					if(cloud == 0)
						cloud = cloud_reader.get_cloud(pcd_data_folder + ask_for_file_name());
					viewer.showCloud(cloud);
					
					cout << "\nEnter number of neighbors for Mean distance: "; 
					cin >> MinNeighborsforMeanDistance;
					cout << "\nEnter standard deviation from Mean distance:"; 
					cin >> StandardDeviationfromMeanDistance;
					
					Filters::statisticaloutlierremoval(cloud, cloud, MinNeighborsforMeanDistance, StandardDeviationfromMeanDistance);
					cout << "\nPoint Cloud is filtered.. \n";
				}
		break;
		
		case '7':
					/*Apply Radius outlier filter:
					 *To apply this filter,number of neighobors to consider for Mean distance and standard deviation
					 *from mean distance is required
					 */
				{
					int MinNeighborsInRadius = 0;
					float RadiusSearch = 0.0f;
					if(cloud == 0)
						cloud = cloud_reader.get_cloud(pcd_data_folder + ask_for_file_name());
					viewer.showCloud(cloud);
					
					cout << "\nEnter minimum neighbors in radius: "; 
					cin >> MinNeighborsInRadius;
					cout << "\nEnter search radius:"; 
					cin >> RadiusSearch;
					
					Filters::radiusoutlierremoval(cloud, cloud, MinNeighborsInRadius, RadiusSearch);
					cout << "\nPoint Cloud is filtered.. \n";
				}
		break;
		
		case '8':	//exit
				{
					cout << "\n\nEnd of program"<<endl;
					return 0;
				} 
		break;
		default:
				{
					cout << "\n\nInvalid option\n\n";
					option = 0;
				}
		break;
	}
	
	if(option != 0)
	 viewer.showCloud(cloud);
	option = 0;
}
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
	<< "6. Apply Statistical outlier filter\n"
	<< "7. Apply Radius outlier filter\n"
	<< "8. Exit.\n\n";
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
	cout << "\nSelect the range & Specify the axis of filtration";
	cout << "\nRange along x-axis:[" << range.min_x << "," << range.max_x<<"]";
	cout << "\nRange along y-axis:[" << range.min_y << "," << range.max_y<<"]";
	cout << "\nRange along z-axis:[" << range.min_z << "," << range.max_z<<"]"<<endl;
}
void cloud_cb_(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr &cloud){
	if(!viewer.wasStopped()){
		viewer.showCloud(cloud);
	}
}

