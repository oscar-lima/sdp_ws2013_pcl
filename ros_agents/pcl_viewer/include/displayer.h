/*
 * displayer.h
 *
 *  Created on: Dec 1, 2013
 *      Author: Iuri Andrade
 */

#ifndef DISPLAYER_H_
#define DISPLAYER_H_

#include <pcl/visualization/cloud_viewer.h>

typedef pcl::PointCloud<pcl::PointXYZ> CloudXYZ;

class Displayer
{
public:
	Displayer();
	~Displayer();
	void setDisplayedCloud(CloudXYZ::Ptr &cloud);
	CloudXYZ::Ptr getDisplayedCloud();
	bool wasStopped();
private:
	CloudXYZ::Ptr displayed_cloud_;
	pcl::visualization::CloudViewer *viewer_;	
};

#endif /* DISPLAYER_H_ */
