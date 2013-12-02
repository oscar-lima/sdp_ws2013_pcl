

#include "passthrough_filter.h"


void passthroughFilter::applyFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest)
{
	// Create the filtering object
	pcl::PassThrough<pcl::PointXYZ> pass;
	pass.setInputCloud(src);
	pass.setFilterFieldName(filter_axis);
	pass.setFilterLimits(range_min,range_max);
	//pass.setFilterLimitsNegative(true);
	pass.filter(*dest);
}
	
void passthroughFilter::setFilterAxis(std::string filter_axis)
{
	filter_axis = filter_axis;
}

void passthroughFilter::setMinRange(float range_min)
{
	range_min = range_min;
}

void passthroughFilter::setMaxRange(float range_max)
{
	range_max = range_max;
}
