#include <ros/ros.h>
#include "pcl_ros/point_cloud.h"
#include "radiusoutlierremoval_filter.h"
#include <dynamic_reconfigure/server.h>
#include <pcl_filters/radiusoutlierremovalConfig.h>

typedef pcl::PointCloud<pcl::PointXYZ>::Ptr CloudXYZ;
ros::Publisher pub_;
ros::Subscriber sub_;
RadiusOutlierFilter filter_;
int min_neighbours_;
double search_radius_;
std::string radiusoutlier_sub_;
std::string radiusoutlier_pub_;


void cloudCallback(CloudXYZ src_cloud);
void dynamicReconfigureCallback(pcl_filters::radiusoutlierremovalConfig &config, uint32_t level);

void dynamicReconfigureCallback(pcl_filters::radiusoutlierremovalConfig &config, uint32_t level) 
{	
	ros::NodeHandle nh("~");
	if (min_neighbours_ != config.min_neighbours)
	{
		min_neighbours_ = config.min_neighbours;
	}
	if (search_radius_ != config.search_radius)
	{
		search_radius_ = config.search_radius;
	}
	std::string temp_str = config.radiusoutlierremoval_sub.c_str();
	if (!config.radiusoutlierremoval_sub.empty() && radiusoutlier_sub_.compare(temp_str) !=0)
	{
		radiusoutlier_sub_ = config.radiusoutlierremoval_sub.c_str();
		sub_.shutdown();
		sub_ = nh.subscribe (radiusoutlier_sub_, 1, cloudCallback);
	}
	ROS_INFO("Reconfigure Request: %d %f",min_neighbours_,search_radius_);
}
void cloudCallback(CloudXYZ src_cloud)
{
	ROS_INFO("cloud_callback");
	filter_.setMinNeighbours(min_neighbours_);
	filter_.setSearchRadius(search_radius_);
	filter_.applyFilter(src_cloud,src_cloud);
	pub_.publish(src_cloud); 
}

int main (int argc, char** argv)
{
	// Initialize ROS
	ros::init (argc, argv, "radiusoutlierremoval_filter");
	min_neighbours_ = 0;
	search_radius_ = 0.0f;
	ros::NodeHandle nh("~");
	pub_ = nh.advertise<pcl::PointCloud<pcl::PointXYZ> > ("output_cloud", 1);
	dynamic_reconfigure::Server<pcl_filters::radiusoutlierremovalConfig> server;
	dynamic_reconfigure::Server<pcl_filters::radiusoutlierremovalConfig>::CallbackType f;
	f = boost::bind(&dynamicReconfigureCallback, _1, _2);
	server.setCallback(f);
	ros::spin();
}
