#include <ros/ros.h>
#include "pcl_ros/point_cloud.h"
#include "passthrough_filter.h"
#include <pcl/visualization/cloud_viewer.h>
#include <dynamic_reconfigure/server.h>
#include <pcl_filters/passthroughConfig.h>
typedef pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud;
ros::Publisher pub;
ros::Subscriber sub;
passthroughFilter test;
std::string axis;
double min_range;
double max_range;
std::string passthrough_sub;
std::string passthrough_pub;


void cloud_cb(point_cloud src_cloud);
void dynamic_reconfigure_callback(pcl_filters::passthroughConfig &config, uint32_t level);

void dynamic_reconfigure_callback(pcl_filters::passthroughConfig &config, uint32_t level) 
{	
	ros::NodeHandle nh("~");
	axis = config.filteration_axis.c_str();
	min_range = config.min_range;
	max_range = config.max_range;
	passthrough_sub = config.passthrough_sub.c_str();
	passthrough_pub = config.passthrough_pub.c_str();
	
	ROS_INFO("Reconfigure Request: %s %f %f",axis.c_str(), min_range,max_range);
	sub.shutdown();
	pub.shutdown();
	sub = nh.subscribe (passthrough_sub, 1, cloud_cb);
	pub = nh.advertise<pcl::PointCloud<pcl::PointXYZ> > (passthrough_pub, 1);
}

void cloud_cb(point_cloud src_cloud)
{
	test.cloud_ranges_find(src_cloud);
	test.setFilterAxis(axis);
	test.setMinRange(min_range);
	test.setMaxRange(max_range);
	test.applyFilter(src_cloud,src_cloud);
	pub.publish(src_cloud); 
}

int main (int argc, char** argv)
{
	// Initialize ROS
	ros::init (argc, argv, "passthrough_filter");
	min_range = 0.0f;
	max_range = 0.0f;
	dynamic_reconfigure::Server<pcl_filters::passthroughConfig> server;
	dynamic_reconfigure::Server<pcl_filters::passthroughConfig>::CallbackType f;
	f = boost::bind(&dynamic_reconfigure_callback, _1, _2);
	server.setCallback(f);
	ros::spin();
}
