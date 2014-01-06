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
	if (axis.compare(config.filteration_axis.c_str()) != 0)
		axis = config.filteration_axis.c_str();
	if(min_range != config.min_range)
		min_range = config.min_range;
	if(max_range != config.max_range)
		max_range = config.max_range;
	std::string temp_str = config.passthrough_sub.c_str();
	if (!config.passthrough_sub.empty() && passthrough_sub.compare(temp_str) != 0)
	{
		sub.shutdown();
		passthrough_sub = config.passthrough_sub.c_str();
		sub = nh.subscribe (passthrough_sub, 1, cloud_cb);
	}
	ROS_INFO("Reconfigure Request: %s %f %f",axis.c_str(), min_range,max_range);
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
	ros::NodeHandle nh("~");
	pub = nh.advertise<pcl::PointCloud<pcl::PointXYZ> > ("output_cloud", 1);
	min_range = 0.0f;
	max_range = 0.0f;
	dynamic_reconfigure::Server<pcl_filters::passthroughConfig> server;
	dynamic_reconfigure::Server<pcl_filters::passthroughConfig>::CallbackType f;
	f = boost::bind(&dynamic_reconfigure_callback, _1, _2);
	server.setCallback(f);
	ros::spin();
}
