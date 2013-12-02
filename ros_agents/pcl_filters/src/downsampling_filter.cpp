

#include "downsampling_filter.h"

void downsamplingFilter::applyFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest)
{
	pcl::VoxelGrid<pcl::PointXYZ> sor;
	sor.setInputCloud (src);
	sor.setLeafSize(voxel_width, voxel_length,voxel_height);
	sor.filter (*dest);
}


void downsamplingFilter::setVoxelWidth(float voxel_grid_size_x)
{
	voxel_width = voxel_grid_size_x;
}

void downsamplingFilter::setVoxelLength(float voxel_grid_size_y)
{
	voxel_length = voxel_grid_size_y;
}

void downsamplingFilter::setVoxelHeight(float voxel_grid_size_z)
{
	voxel_height = voxel_grid_size_z;
}
