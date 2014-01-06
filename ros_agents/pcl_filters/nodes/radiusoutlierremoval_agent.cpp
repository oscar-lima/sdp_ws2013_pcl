#include <ros/ros.h>
#include "pcl_ros/point_cloud.h"
#include "radiusoutlierremoval_filter.h"
#include <dynamic_reconfigure/server.h>
#include <pcl_filters/radiusoutlierremovalConfig.h>

typedef pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud;
ros::Publisher pub;
ros::Subscriber sub;
radiusoutlierremovalFilter test;
int min_neighbours;
double search_radius;
std::string radiusoutlierremoval_sub;
std::string radiusoutlierremoval_pub;


void cloud_cb(point_cloud src_cloud);
void dynamic_reconfigure_callback(pcl_filters::radiusoutlierremovalConfig &config, uint32_t level);

void dynamic_reconfigure_callback(pcl_filters::radiusoutlierremovalConfig &config, uint32_t level) 
{	
	ros::NodeHandle nh("~");
	if(min_neighbours != config.min_neighbours)
		min_neighbours = config.min_neighbours;
	if(search_radius != config.search_radius)
		search_radius = config.search_radius;
	std::string temp_str = config.radiusoutlierremoval_sub.c_str();
	if(!config.radiusoutlierremoval_sub.empty() && radiusoutlierremoval_sub.compare(temp_str) !=0)
	{
		radiusoutlierremoval_sub = config.radiusoutlierremoval_sub.c_str();
		sub.shutdown();
		sub = nh.subscribe (radiusoutlierremoval_sub, 1, cloud_cb);
	}
	ROS_INFO("Reconfigure Request: %d %f",min_neighbours,search_radius);
}
void cloud_cb(point_cloud src_cloud)
{
	test.setMinNeighbours(min_neighbours);
	test.setSearchRadius(search_radius);
	test.applyFilter(src_cloud,src_cloud);
	pub.publish(src_cloud); 
}

int main (int argc, char** argv)
{
	// Initialize ROS
	ros::init (argc, argv, "radiusoutlierremoval_filter");
	int min_neighbours = 0;
	double search_radius = 0.0f;
	ros::NodeHandle nh("~");
	pub = nh.advertise<pcl::PointCloud<pcl::PointXYZ> > ("output_cloud", 1);
	dynamic_reconfigure::Server<pcl_filters::radiusoutlierremovalConfig> server;
	dynamic_reconfigure::Server<pcl_filters::radiusoutlierremovalConfig>::CallbackType f;
	f = boost::bind(&dynamic_reconfigure_callback, _1, _2);
	server.setCallback(f);

	ros::spin();
}
