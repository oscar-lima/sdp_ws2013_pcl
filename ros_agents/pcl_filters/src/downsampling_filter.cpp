

#include "downsampling_filter.h"

void DownsamplingFilter::applyFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest)
{
	pcl::VoxelGrid<pcl::PointXYZ> sor;
	sor.setInputCloud (src);
	sor.setLeafSize(voxel_width_, voxel_length_,voxel_height_);
	sor.filter (*dest);
}


void DownsamplingFilter::setVoxelWidth(float voxel_grid_size_x)
{
	voxel_width_ = voxel_grid_size_x;
}

void DownsamplingFilter::setVoxelLength(float voxel_grid_size_y)
{
	voxel_length_ = voxel_grid_size_y;
}

void DownsamplingFilter::setVoxelHeight(float voxel_grid_size_z)
{
	voxel_height_ = voxel_grid_size_z;
}
