#include <ros/ros.h>
#include <pcl/visualization/cloud_viewer.h>
#include "pcd_simple_io.h"
#include "pcl_ros/point_cloud.h"

PCDSimpleIO cloud_reader;
ros::Publisher pub;

int main (int argc, char** argv)
{
	ros::init (argc, argv, "pcl_reader_tester");
	ros::NodeHandle nh;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
	
	cloud = cloud_reader.getCloud("table.pcd");
	pub = nh.advertise<pcl::PointCloud<pcl::PointXYZ> > ("cloud", 1);
		
	while(pub.getNumSubscribers() == 0 && ros::ok())
	{
		ros::Duration(1).sleep();
		ROS_INFO("Waiting for cloud listener... %f",ros::Time::now().toSec());
	}
	pub.publish(cloud);
}
