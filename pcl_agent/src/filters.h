/*
 * Filters.h
 *
 *  Created on: Oct 23, 2013
 *      Author: Shehzad Ahmed
 */

#ifndef FILTERS_H_
#define FILTERS_H_

class Filters
{
public:
	Filters();
	void filter_Passthrough(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest ,const char* filter_axis,float range_min,float range_max);
	void filter_Downsampling(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest ,float voxel_grid_size_x,float voxel_grid_size_y,float voxel_grid_size_z);
	//void filter_Downsampling(boost::shared_ptr<pcl::PointCloud<pcl::PointXYZ> >::Ptr src, boost::shared_ptr<pcl::PointCloud<pcl::PointXYZ> >::Ptr dest ,float lx,float ly,float lz);

};

#endif /* FILTERS_H_ */
