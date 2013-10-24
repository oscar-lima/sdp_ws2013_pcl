/*
 * Visualization.h
 *
 *  Created on: Oct 23, 2013
 *      Author: iuriaa
 */

#ifndef AGENTVIEWER_H_
#define AGENTVIEWER_H_

#include <iostream>
#include <boost/thread/thread.hpp>
#include <pcl/common/common_headers.h>
#include <pcl/features/normal_3d.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>

class AgentViewer {
public:
	AgentViewer(pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud);
	//virtual ~AgentViewer();
private:
	boost::shared_ptr<pcl::visualization::PCLVisualizer> simpleVis(pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud);
	boost::shared_ptr<pcl::visualization::PCLVisualizer> customColourVis (pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud);
};

#endif /* VISUALIZATION_H_ */
