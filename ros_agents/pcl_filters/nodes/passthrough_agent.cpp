#include <ros/ros.h>
#include "pcl_ros/point_cloud.h"
#include "passthrough_filter.h"
#include <pcl/visualization/cloud_viewer.h>
#include <dynamic_reconfigure/server.h>
#include <pcl_filters/passthroughConfig.h>

typedef pcl::PointCloud<pcl::PointXYZ>::Ptr CloudXYZ;
ros::Publisher pub_;
ros::Subscriber sub_;
PassthroughFilter test_;
std::string axis_;
double min_range_;
double max_range_;
std::string passthrough_sub_;
std::string passthrough_pub_;


void cloudCallback(CloudXYZ src_cloud);
void dynamicReconfigureCallback(pcl_filters::passthroughConfig &config, uint32_t level);

void dynamicReconfigureCallback(pcl_filters::passthroughConfig &config, uint32_t level) 
{
	ros::NodeHandle nh("~");
	if (axis_.compare(config.filteration_axis.c_str()) != 0)
	{
		axis_ = config.filteration_axis.c_str();
	}
	if (min_range_ != config.min_range)
	{
		min_range_ = config.min_range;
	}
	if (max_range_ != config.max_range)
	{
		max_range_ = config.max_range;
	}
	
	std::string temp_str = config.passthrough_sub.c_str();
	if (!config.passthrough_sub.empty() && passthrough_sub_.compare(temp_str) != 0)
	{
		sub_.shutdown();
		passthrough_sub_ = config.passthrough_sub.c_str();
		sub_ = nh.subscribe (passthrough_sub_, 1, cloudCallback);
	}
	ROS_INFO("Reconfigure Request: %s %f %f",axis_.c_str(), min_range_,max_range_);
}

void cloudCallback(CloudXYZ src_cloud)
{
	test_.cloudRangesFind(src_cloud);
	test_.setFilterAxis(axis_);
	test_.setMinRange(min_range_);
	test_.setMaxRange(max_range_);
	test_.applyFilter(src_cloud,src_cloud);
	pub_.publish(src_cloud); 
}

int main (int argc, char** argv)
{
	// Initialize ROS
	ros::init (argc, argv, "passthrough_filter");
	ros::NodeHandle nh("~");
	pub_ = nh.advertise<pcl::PointCloud<pcl::PointXYZ> > ("output_cloud", 1);
	min_range_ = 0.0f;
	max_range_ = 0.0f;
	dynamic_reconfigure::Server<pcl_filters::passthroughConfig> server;
	dynamic_reconfigure::Server<pcl_filters::passthroughConfig>::CallbackType f;
	f = boost::bind(&dynamicReconfigureCallback, _1, _2);
	server.setCallback(f);
	ros::spin();
}
