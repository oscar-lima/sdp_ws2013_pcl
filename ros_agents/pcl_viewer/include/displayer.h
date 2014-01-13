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
	Displayer(): viewer_("Cloud Viewer"){};
	void setDisplayedCloud(const CloudXYZ::ConstPtr &cloud);
	bool wasStopped();
private:
	pcl::visualization::CloudViewer viewer_;	
};

#endif /* DISPLAYER_H_ */
