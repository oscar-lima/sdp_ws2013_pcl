#include <ros/ros.h>
// PCL specific includes
#include "pcl_ros/point_cloud.h"
#include <pcl/visualization/cloud_viewer.h>

pcl::visualization::CloudViewer viewer("Cloud Viewer");

void cloud_cb(const point_cloud cloud){
 viewer.showCloud(cloud);
}

int main (int argc, char** argv){
  // Initialize ROS
  ros::init(argc, argv, "pcl_viewer");
  ros::NodeHandle nh;
  // Create a ROS subscriber for the input point cloud
  ros::Subscriber sub = nh.subscribe("cloud", 1, cloud_cb);

  // Spin
  ros::spin();
}
