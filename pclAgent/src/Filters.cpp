#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/voxel_grid.h>


#include "Filters.h"

    Filters::Filters(){

    }

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

	void filter_voxel(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest ,float lx,float ly,float lz){

		  pcl::VoxelGrid<pcl::PointXYZ> sor;
		  sor.setInputCloud (src);
		  sor.setLeafSize(lx, ly, lz);
		  sor.filter (*dest);
	}

