

#include "passthrough_filter.h"


void passthroughFilter::applyFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest)
	{
			// Create the filtering object
			  pcl::PassThrough<pcl::PointXYZ> pass;
			  const char *filtration_axis_ptr = &(passthroughFilter::filter_axis);
			  pass.setInputCloud(src);
			  pass.setFilterFieldName(filtration_axis_ptr);
			  pass.setFilterLimits(passthroughFilter::range_min,passthroughFilter::range_max);
			  //pass.setFilterLimitsNegative(true);
			  pass.filter(*dest);
	}
	
void passthroughFilter::setParams(char filter_axis,float range_min,float range_max){
		passthroughFilter::filter_axis = filter_axis;
		passthroughFilter::range_min = range_min;
		passthroughFilter::range_max = range_max;
	}

