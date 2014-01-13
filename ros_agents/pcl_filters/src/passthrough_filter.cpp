

#include "passthrough_filter.h"

void PassthroughFilter::applyFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest)
{
	// Create the filtering object
	pcl::PassThrough<pcl::PointXYZ> pass;
	pass.setInputCloud(src);
	pass.setFilterFieldName(filter_axis_);
	pass.setFilterLimits(range_min_limit_,range_max_limit_);
	//pass.setFilterLimitsNegative(true);
	pass.filter(*dest);
}
	
void PassthroughFilter::setFilterAxis(std::string axis)
{
	filter_axis_ = axis;
}

void PassthroughFilter::setMinRange(float range_min)
{
	range_min_limit_ = range_min;
}

void PassthroughFilter::setMaxRange(float range_max)
{
	range_max_limit_ = range_max;
}

void PassthroughFilter::cloudRangesFind(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
{
	RangeAxis range;
	for (size_t i = 0; i < cloud->points.size(); ++i)
	{
		if (cloud->points[i].x > range.max_x)
		{
			range.max_x = cloud->points[i].x;
		} 
		else if (cloud->points[i].x < range.min_x)
		{
			range.min_x = cloud->points[i].x;
		}
		
		if (cloud->points[i].y > range.max_y)
		{
			range.max_y = cloud->points[i].y;
		}
		else if (cloud->points[i].y < range.min_y)
		{
			range.min_y= cloud->points[i].y;
		}
		
		if (cloud->points[i].z > range.max_z)
		{
			range.max_z = cloud->points[i].z;
		}
		else if (cloud->points[i].z < range.min_z)
		{
			range.min_z= cloud->points[i].z;
		}
	}
	std::cout << "\nSelect the range & Specify the axis of filtration";
	std::cout << "\nRange along x-axis:[" << range.min_x << "," << range.max_x<<"]";
	std::cout << "\nRange along y-axis:[" << range.min_y << "," << range.max_y<<"]";
	std::cout << "\nRange along z-axis:[" << range.min_z << "," << range.max_z<<"]"<<std::endl;
}
