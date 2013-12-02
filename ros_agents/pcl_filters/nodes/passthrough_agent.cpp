#include <ros/ros.h>
#include "pcl_ros/point_cloud.h"
#include "passthrough_filter.h"
#include <pcl/visualization/cloud_viewer.h>
typedef pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud;
ros::Publisher pub;
passthroughFilter test;
void cloud_ranges_find(point_cloud cloud);



void cloud_cb(point_cloud src_cloud)
{
	//point_cloud dest_cloud
	cloud_ranges_find(src_cloud);
	std::string axis = "x";
	//char *axis("x");
	test.setFilterAxis(axis);
	test.setMinRange(0.0);
	test.setMaxRange(0.5);
	test.applyFilter(src_cloud,src_cloud);
	pub.publish(src_cloud); 
	
	pub.shutdown();
}
void cloud_ranges_find(point_cloud cloud){

	struct range_axis{
		float max_x;
		float min_x;
		float max_y;
		float min_y;
		float max_z;
		float min_z;
	}range;
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
	std::cout << "\nSelect the range & Specify the axis of filtration";
	std::cout << "\nRange along x-axis:[" << range.min_x << "," << range.max_x<<"]";
	std::cout << "\nRange along y-axis:[" << range.min_y << "," << range.max_y<<"]";
	std::cout << "\nRange along z-axis:[" << range.min_z << "," << range.max_z<<"]"<<std::endl;
}

int main (int argc, char** argv)
{
	// Initialize ROS
	ros::init (argc, argv, "passthrough_filter");
	ros::NodeHandle nh;
	// Create a ROS subscriber for the input point cloud
	ros::Subscriber sub = nh.subscribe ("/cloud", 1, cloud_cb);

	//Create a ROS publisher for the output point cloud
	pub = nh.advertise<pcl::PointCloud<pcl::PointXYZ> > ("/filtered_cloud", 1);

	ros::spin();
}
