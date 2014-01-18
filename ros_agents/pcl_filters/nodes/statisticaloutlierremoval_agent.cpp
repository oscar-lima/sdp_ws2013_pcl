#include <ros/ros.h>
#include "pcl_ros/point_cloud.h"
#include "statisticaloutlierremoval_filter.h"
#include <dynamic_reconfigure/server.h>
#include <pcl_filters/statisticaloutlierremovalConfig.h>

typedef pcl::PointCloud<pcl::PointXYZ>::Ptr CloudXYZ;
ros::Publisher pub_;
ros::Subscriber sub_;
StatisticalOutlierFilter filter_;
int neighbours_;
double standard_deviation_;
std::string statisticaloutlierremoval_sub_;
std::string statisticaloutlierremoval_pub_;

void cloudCallback(CloudXYZ src_cloud);
void dynamiReconfigureCallback(pcl_filters::statisticaloutlierremovalConfig &config, uint32_t level);

void dynamicReconfigureCallback(pcl_filters::statisticaloutlierremovalConfig &config, uint32_t level) 
{	
	ros::NodeHandle nh("~");
	if (neighbours_ != config.neighbours)
	{
		neighbours_ = config.neighbours;
	}
	if (standard_deviation_ != config.standard_deviation)
	{
		standard_deviation_ = config.standard_deviation;
	}
	std::string temp_str = config.statisticaloutlierremoval_sub.c_str();
	if (!config.statisticaloutlierremoval_sub.empty() && statisticaloutlierremoval_sub_.compare(temp_str) != 0)
	{
		sub_.shutdown();
		statisticaloutlierremoval_sub_ = config.statisticaloutlierremoval_sub.c_str();
		sub_ = nh.subscribe(statisticaloutlierremoval_sub_, 1, cloudCallback);
	}
	ROS_INFO("Reconfigure Request: %d %f",neighbours_,standard_deviation_);
}

void cloudCallback(CloudXYZ src_cloud)
{
	//point_cloud dest_cloud
	filter_.setNeighbours(neighbours_);
	filter_.setStandardDeviation(standard_deviation_);
	filter_.applyFilter(src_cloud,src_cloud);
	pub_.publish(src_cloud); 
}

int main(int argc, char** argv)
{
	// Initialize ROS
	ros::init (argc, argv, "statisticaloutlierremoval_filter");
	neighbours_ = 0;
	standard_deviation_ = 0.0f;
	ros::NodeHandle nh("~");
	pub_ = nh.advertise<pcl::PointCloud<pcl::PointXYZ> >("output_cloud", 1);
	dynamic_reconfigure::Server<pcl_filters::statisticaloutlierremovalConfig> server;
	dynamic_reconfigure::Server<pcl_filters::statisticaloutlierremovalConfig>::CallbackType f;
	f = boost::bind(&dynamicReconfigureCallback, _1, _2);
	server.setCallback(f);
	ros::spin();
}
