

#include "passthrough_filter.h"


void passthroughFilter::applyFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest)
{
	// Create the filtering object
	pcl::PassThrough<pcl::PointXYZ> pass;
	pass.setInputCloud(src);
	pass.setFilterFieldName(filter_axis);
	pass.setFilterLimits(range_min_limit,range_max_limit);
	//pass.setFilterLimitsNegative(true);
	pass.filter(*dest);
}
	
void passthroughFilter::setFilterAxis(std::string axis)
{
	filter_axis = axis;
}

void passthroughFilter::setMinRange(float range_min)
{
	range_min_limit = range_min;
}

void passthroughFilter::setMaxRange(float range_max)
{
	range_max_limit = range_max;
}

void passthroughFilter::cloud_ranges_find(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
{
	struct range_axis{
		float max_x;
		float min_x;
		float max_y;
		float min_y;
		float max_z;
		float min_z;
	}range;
	
	 for (size_t i = 0; i < cloud->points.size(); ++i){
		 if(cloud->points[i].x > range.max_x)
		    {range.max_x = cloud->points[i].x;}
		 else if(cloud->points[i].x < range.min_x)
		   { range.min_x = cloud->points[i].x;}
		 if(cloud->points[i].y > range.max_y)
		    {range.max_y = cloud->points[i].y;}
		 else if(cloud->points[i].y < range.min_y)
		   { range.min_y= cloud->points[i].y;}
		 if(cloud->points[i].z > range.max_z)
		    {range.max_z = cloud->points[i].z;}
		 else if(cloud->points[i].z < range.min_z)
		   { range.min_z= cloud->points[i].z;}
	}
	std::cout << "\nSelect the range & Specify the axis of filtration";
	std::cout << "\nRange along x-axis:[" << range.min_x << "," << range.max_x<<"]";
	std::cout << "\nRange along y-axis:[" << range.min_y << "," << range.max_y<<"]";
	std::cout << "\nRange along z-axis:[" << range.min_z << "," << range.max_z<<"]"<<std::endl;
}
