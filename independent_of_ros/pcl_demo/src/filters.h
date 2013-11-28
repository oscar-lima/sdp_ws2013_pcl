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
	static void passthrough(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest ,const char* filter_axis,float range_min,float range_max);
	static void downsampling(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest ,float voxel_grid_size_x,float voxel_grid_size_y,float voxel_grid_size_z);
	static void statisticaloutlierremoval(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest ,int MeanKNeighbors,float StddevMulThresh);
	static void radiusoutlierremoval(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest ,int MinNeighborsInRadius,float RadiusSearch);
	//void filter_Downsampling(boost::shared_ptr<pcl::PointCloud<pcl::PointXYZ> >::Ptr src, boost::shared_ptr<pcl::PointCloud<pcl::PointXYZ> >::Ptr dest ,float lx,float ly,float lz);
};

#endif /* FILTERS_H_ */
