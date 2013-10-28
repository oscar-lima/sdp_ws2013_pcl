#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/voxel_grid.h>


#include "filters.h"

	void Filters::filter_Passthrough(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest ,const char* filter_axis,float range_min,float range_max)
	{
			// Create the filtering object
			  pcl::PassThrough<pcl::PointXYZ> pass;
			  pass.setInputCloud(src);
			  pass.setFilterFieldName(filter_axis);
			  pass.setFilterLimits(range_min, range_max);
			  //pass.setFilterLimitsNegative(true);
			  pass.filter(*dest);
	}

	void Filters::filter_Downsampling(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest ,float voxel_grid_size_x,float voxel_grid_size_y,float voxel_grid_size_z){

		  pcl::VoxelGrid<pcl::PointXYZ> sor;
		  sor.setInputCloud (src);
		  sor.setLeafSize(voxel_grid_size_x, voxel_grid_size_y, voxel_grid_size_z);
		  sor.filter (*dest);
	}
	

