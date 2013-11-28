    /*
 * cloud_viewer.cpp
 *
 *  Created on: Oct 23, 2013
 *      Author: Iuri Andrade
 */

#include "cloud_viewer.h"

CloudViewer::CloudViewer() {
    
}

/*
 * For adding other visualizations later..
boost::shared_ptr<pcl::visualization::PCLVisualizer> CloudViewer::customColourVis (pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud)
{
  // --------------------------------------------
  // -----Open 3D viewer and add point cloud-----
  // --------------------------------------------
  viewer = new pcl::visualization::PCLVisualizer ("3D Viewer");
  viewer->setBackgroundColor (0, 0, 0);
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color(cloud, 0, 255, 0);
  viewer->addPointCloud<pcl::PointXYZ>(cloud, single_color, "sample cloud");
  viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");
  viewer->addCoordinateSystem (1.0);
  viewer->initCameraParameters ();
  return (viewer);
}*/

boost::shared_ptr<pcl::visualization::PCLVisualizer> CloudViewer::simpleVis(pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud) {
	// --------------------------------------------
	// -----Open 3D viewer and add point cloud-----
	// --------------------------------------------
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
	viewer->removeAllPointClouds();
	viewer->setBackgroundColor(0, 0, 0);
	viewer->addPointCloud<pcl::PointXYZ>(cloud, "sample cloud");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "sample cloud");
	viewer->addCoordinateSystem(1.0);
	viewer->initCameraParameters();
	return viewer;
}
