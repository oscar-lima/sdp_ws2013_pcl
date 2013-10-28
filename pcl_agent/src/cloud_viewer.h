/*
 * cloud_viewer.h
 *
 *  Created on: Oct 23, 2013
 *      Author: Iuri Andrade
 */

#ifndef CLOUDVIEWER_H_
#define CLOUDVIEWER_H_

#include <iostream>
#include <boost/thread/thread.hpp>
#include <pcl/common/common_headers.h>
#include <pcl/features/normal_3d.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>

class CloudViewer {
public:
	CloudViewer(pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud);
	//virtual ~CloudViewer();
private:
	boost::shared_ptr<pcl::visualization::PCLVisualizer> simpleVis(pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud);
	boost::shared_ptr<pcl::visualization::PCLVisualizer> customColourVis(pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud);
};

#endif /* CLOUDVIEWER_H_ */
