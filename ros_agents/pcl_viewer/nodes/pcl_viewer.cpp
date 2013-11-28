#include <ros/ros.h>
// PCL specific includes
#include "pcl_ros/point_cloud.h"
#include <pcl/visualization/cloud_viewer.h>
//#include <pcl/filters/voxel_grid.h>

typedef pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud;
ros::Publisher pub;
pcl::visualization::CloudViewer viewer("Cloud Viewer");

void cloud_cb(const point_cloud cloud)
{
 /*	
  point_cloud cloud_filtered;
  // Perform the actual filtering
  pcl::VoxelGrid<pcl::PointXYZ> sor;
  sor.setInputCloud (cloud);
  sor.setLeafSize (0.01, 0.01, 0.01);
  sor.filter(cloud_filtered);

  // Publish the data
  //pub.publish(cloud_filtered);
 */ 
 viewer.showCloud(cloud);
 
}

int main (int argc, char** argv)
{
  // Initialize ROS
  ros::init (argc, argv, "pcl_viewer");
  ros::NodeHandle nh;
  // Create a ROS subscriber for the input point cloud
  ros::Subscriber sub = nh.subscribe ("/cloud", 1, cloud_cb);

  // Create a ROS publisher for the output point cloud
  //pub = nh.advertise<pcl::PointCloud<pcl::PointXYZ> > ("output", 1);

  // Spin
  ros::spin ();
}
