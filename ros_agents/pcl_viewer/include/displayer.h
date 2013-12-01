/*
 * displayer.h
 *
 *  Created on: Dec 1, 2013
 *      Author: Iuri Andrade
 */

#ifndef DISPLAYER_H_
#define DISPLAYER_H_

#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>

typedef pcl::PointCloud<pcl::PointXYZ> CloudXYZ;

class Displayer {
public:
	//void setParams(bool colored);
	void Displayer();
	void setDisplayedCloud(CloudXYZ::Ptr cloud);
	CloudXYZ::Ptr getDisplayedCloud();
	bool wasStopped();
	
private:
	//bool colored = false;
	CloudXYZ::Ptr displayedCloud;
	pcl::visualization::CloudViewer viewer;
	
};

#endif /* DISPLAYER_H_ */
