/*
 *  radiusoutlierremoval_filter.cpp
 *
 *  Created on: Dec 02, 2013
 *  Author: Shehzad Ahmed
 */

#include "radiusoutlierremoval_filter.h"


void radiusoutlierremovalFilter::applyFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest)
{
	pcl::RadiusOutlierRemoval<pcl::PointXYZ> outrem;
	outrem.setInputCloud(src);
	outrem.setMinNeighborsInRadius(	min_neighbours);
	outrem.setRadiusSearch(search_radius);
	outrem.filter (*dest);
}
	
void radiusoutlierremovalFilter::setMinNeighbours(int neighbours)
{
	min_neighbours = neighbours;
}

void radiusoutlierremovalFilter::setSearchRadius(float radius)
{
	search_radius = radius;
}

