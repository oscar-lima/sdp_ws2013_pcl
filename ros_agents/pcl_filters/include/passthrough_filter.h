/*
 * Filters.h
 *
 *  Created on: Oct 23, 2013
 *      Author: Shehzad Ahmed
 */
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include "filters_interface.h"


#ifndef PASSTHROUGH_FILTERS_H_
#define PASSTHROUGH_FILTERS_H_

class passthroughFilter : public filtersInterface
{
public:

	void applyFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest);
	void setFilterAxis(std::string filter_axis);
	void setMinRange(float range_min);
	void setMaxRange(float range_max);
	void cloud_ranges_find(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
	
	
private:
	std::string filter_axis;
	float range_min_limit;
	float range_max_limit;
};

#endif /* PASSTHROUGH_FILTERS_H_ */

