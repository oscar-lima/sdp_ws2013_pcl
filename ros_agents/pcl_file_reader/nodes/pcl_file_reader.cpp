#include <ros/ros.h>
// PCL specific includes
#include "pcl_ros/point_cloud.h"

#include "pcd_simple_io.h"
#include <pcl/visualization/cloud_viewer.h>


typedef pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud;

PCDSimpleIO cloud_reader;
//pcl::visualization::CloudViewer viewer("Cloud Viewer");
ros::Publisher pub;
/*
void cloud_cb (const sensor_msgs::PointCloud2ConstPtr& cloud)
{
 
}
*/
int main (int argc, char** argv)
{
  // Initialize ROS
  ros::init (argc, argv, "pcl_agent_client");
  ros::NodeHandle nh;
  ROS_INFO("");
	point_cloud cloud;
	cloud = cloud_reader.get_cloud("../data/pcd_files/table.pcd");
	pub = nh.advertise<pcl::PointCloud<pcl::PointXYZ> > ("pcl_file_reader", 1);
	
	//while(1)
	{
		//viewer.showCloud(cloud);
		 pub.publish(cloud);
	}	
  // Create a ROS subscriber for the input point cloud
  
  //ros::Subscriber sub = nh.subscribe ("output", 1, cloud_cb);
  // Create a ROS publisher for the output point cloud
  // Spin
  //ros::spin ();
  return 0;
}
