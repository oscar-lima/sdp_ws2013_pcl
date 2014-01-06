#include <ros/ros.h>
#include <pcl_file_reader/pcl_file_readerConfig.h>
#include <dynamic_reconfigure/server.h>
#include <pcl/visualization/cloud_viewer.h>
#include "pcl_ros/point_cloud.h"
#include <ros/package.h>
#include "std_msgs/String.h"

#include "pcd_simple_io.h"
#include <sys/stat.h>	//to check file existance: http://stackoverflow.com/questions/4316442/stdofstream-check-if-file-exists-before-writing

ros::Publisher cloud_pub;
ros::Subscriber sub;

std::string pcd_path;
std::string pcd_filename;

void dynamicReconfigureCallback(pcl_file_reader::pcl_file_readerConfig &config, uint32_t level) 
{
	ROS_INFO("Reconfigure request received...");
  
	pcd_path = config.pcd_path.c_str();
	pcd_filename = config.pcd_filename.c_str();

	bool file_existance = false;
	const std::string& filename = pcd_path + pcd_filename;

	struct stat buf;
	if (stat(filename.c_str(), &buf) != -1)
	{
		file_existance = true;
	}

	if(pcd_path != "" && pcd_filename != "" && file_existance)
	{
		bool cloud_read_succes = false;
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;

		PCDSimpleIO cloud_reader(pcd_path, pcd_filename);
		cloud = cloud_reader.getCloud2(cloud_read_succes);

		if(cloud_read_succes)
		{
			if (cloud->points.size() != 0)
			{
				ROS_INFO("Cloud succesfully loaded : %lu points", cloud->points.size());
				cloud_pub.publish(cloud);
			}
			else
			{
				ROS_ERROR("Attempting to publish empty cloud");
			}
		}
		else
		{
			ROS_ERROR("Could not read pcd file, ensure that pcd_path and pcd_filename parameters have correct values");
		}
	}
}

int main(int argc, char **argv) 
{
	ros::init (argc, argv, "pcl_file_reader");
	ROS_INFO("pcl_reader node initialized ...");

	ros::NodeHandle nh("~");
	cloud_pub = nh.advertise<pcl::PointCloud<pcl::PointXYZ> > ("output_cloud", 1);
	
	dynamic_reconfigure::Server<pcl_file_reader::pcl_file_readerConfig> reader;
	dynamic_reconfigure::Server<pcl_file_reader::pcl_file_readerConfig>::CallbackType f;

	f = boost::bind(&dynamicReconfigureCallback, _1, _2);
	reader.setCallback(f);

	ros::spin();
}