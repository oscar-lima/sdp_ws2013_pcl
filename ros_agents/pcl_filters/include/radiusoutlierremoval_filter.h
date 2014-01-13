/*
 * radiusoutlierremoval_filter.h
 *
 *  Created on: Dec 02, 2013
 *      Author: Shehzad Ahmed
 */
#include <pcl/point_types.h>
#include <pcl/filters/radius_outlier_removal.h>
#include "filters_interface.h"

#ifndef RADIUSOUTLIERREMOVAL_FILTERS_H_
#define RADIUSOUTLIERREMOVAL_FILTERS_H_

class RadiusOutlierFilter : public FiltersInterface
{
public:
	void applyFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest);
	void setMinNeighbours(int neighbours);
	void setSearchRadius(float radius);

private:
	int min_neighbours_;
	float search_radius_;
};

#endif /* RADIUSOUTLIERREMOVAL_FILTERS_H_ */

