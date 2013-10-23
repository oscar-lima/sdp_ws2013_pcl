/*
 * Filters.h
 *
 *  Created on: Oct 23, 2013
 *      Author: shehzad
 */

#ifndef FILTERS_H_
#define FILTERS_H_

class Filters
{
public:
	Filters();
	void filter_Passthrough(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest ,const char* filter_axis,float range_min,float range_max);
	void filter_voxel(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest ,float lx,float ly,float lz);

};

#endif /* FILTERS_H_ */
