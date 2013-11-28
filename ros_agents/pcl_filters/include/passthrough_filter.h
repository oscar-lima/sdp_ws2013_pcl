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
	void setParams(char filter_axis,float range_min,float range_max);
	
private:
char filter_axis;
float range_min;
float range_max;
};

#endif /* PASSTHROUGH_FILTERS_H_ */

