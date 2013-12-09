/*
 * displayer.cpp
 *
 *  Created on: Dec 1, 2013
 *      Author: Iuri Andrade
 */

#include "displayer.h"

Displayer::Displayer(){
	viewer = new pcl::visualization::CloudViewer("Cloud Viewer");
}

Displayer::~Displayer(){
	delete(viewer);
}

void Displayer::setDisplayedCloud(CloudXYZ::Ptr &cloud){
	viewer->showCloud(cloud);
	displayedCloud = cloud;
}

CloudXYZ::Ptr Displayer::getDisplayedCloud(){
	return displayedCloud;
}

bool Displayer::wasStopped(){
	return viewer->wasStopped();
}
