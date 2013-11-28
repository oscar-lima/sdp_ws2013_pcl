#include <ros/ros.h>
#include "pcl_ros/point_cloud.h"
#include "passthrough_filter.h"

typedef pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud;
ros::Publisher pub;

void cloud_cb(point_cloud src_cloud)
{
 //point_cloud dest_cloud;
  passthroughFilter ;
   test.setParams('x',0.0,0.5);
  test.applyFilter(src_cloud,src_cloud);

  pub.publish(src_cloud); 
 
}

int main (int argc, char** argv)
{
  // Initialize ROS
  ros::init (argc, argv, "passthrough_ros");
  ros::NodeHandle nh;
  // Create a ROS subscriber for the input point cloud
  ros::Subscriber sub = nh.subscribe ("pcl_file_reader", 1, cloud_cb);

  //Create a ROS publisher for the output point cloud
 pub = nh.advertise<pcl::PointCloud<pcl::PointXYZ> > ("pcl_file_reader", 1);

  ros::spin();
}
