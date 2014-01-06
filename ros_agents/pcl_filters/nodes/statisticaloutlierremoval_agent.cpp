#include <ros/ros.h>
#include "pcl_ros/point_cloud.h"
#include "statisticaloutlierremoval_filter.h"
#include <dynamic_reconfigure/server.h>
#include <pcl_filters/statisticaloutlierremovalConfig.h>

typedef pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud;
ros::Publisher pub;
ros::Subscriber sub;
statisticaloutlierremovalFilter test;

int neighbours;
double standard_deviation;
std::string statisticaloutlierremoval_sub;
std::string statisticaloutlierremoval_pub;


void cloud_cb(point_cloud src_cloud);
void dynamic_reconfigure_callback(pcl_filters::statisticaloutlierremovalConfig &config, uint32_t level);

void dynamic_reconfigure_callback(pcl_filters::statisticaloutlierremovalConfig &config, uint32_t level) 
{	
	ros::NodeHandle nh("~");
	neighbours = config.neighbours;
	standard_deviation = config.standard_deviation;
	statisticaloutlierremoval_sub = config.statisticaloutlierremoval_sub.c_str();
	statisticaloutlierremoval_pub = config.statisticaloutlierremoval_pub.c_str();
	
	ROS_INFO("Reconfigure Request: %d %f",neighbours,standard_deviation);
	sub.shutdown();
	pub.shutdown();
	sub = nh.subscribe (statisticaloutlierremoval_sub, 1, cloud_cb);
	pub = nh.advertise<pcl::PointCloud<pcl::PointXYZ> > (statisticaloutlierremoval_pub, 1);
}

void cloud_cb(point_cloud src_cloud)
{
	//point_cloud dest_cloud
	test.setNeighbours(neighbours);
	test.setStandardDeviation(standard_deviation);
	test.applyFilter(src_cloud,src_cloud);
	pub.publish(src_cloud); 
	
}

int main (int argc, char** argv)
{
	// Initialize ROS
	ros::init (argc, argv, "statisticaloutlierremoval_filter");
	neighbours = 0;
	standard_deviation = 0.0f;
	dynamic_reconfigure::Server<pcl_filters::statisticaloutlierremovalConfig> server;
	dynamic_reconfigure::Server<pcl_filters::statisticaloutlierremovalConfig>::CallbackType f;
	f = boost::bind(&dynamic_reconfigure_callback, _1, _2);
	server.setCallback(f);


	ros::spin();
}
