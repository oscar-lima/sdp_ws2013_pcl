/*
 *  radiusoutlierremoval_filter.cpp
 *  Created on: Dec 02, 2013
 *  Author: Shehzad Ahmed
 */

#include "radiusoutlierremoval_filter.h"

void RadiusOutlierFilter::applyFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest)
{
	pcl::RadiusOutlierRemoval<pcl::PointXYZ> outrem;
	outrem.setInputCloud(src);
	outrem.setMinNeighborsInRadius(min_neighbours_);
	outrem.setRadiusSearch(search_radius_);
	outrem.filter (*dest);
}

void RadiusOutlierFilter::setMinNeighbours(int neighbours)
{
	min_neighbours_ = neighbours;
}

void RadiusOutlierFilter::setSearchRadius(float radius)
{
	search_radius_ = radius;
}

