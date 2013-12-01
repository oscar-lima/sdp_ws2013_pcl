/*
 * displayer.cpp
 *
 *  Created on: Dec 1, 2013
 *      Author: Iuri Andrade
 */

#include "displayer.h"

void Displayer::Displayer(){
	Displayer::viewer = new CloudViewer("Cloud Viewer");
}

void Displayer::setDisplayedCloud(CloudXYZ::Ptr cloud){
	Displayer::viewer.showCloud(cloud);
	Displayer::displayedCloud = cloud;
}

CloudXYZ::Ptr Displayer::getDisplayedCloud(){
	return Displayer::displayedCloud;
}

bool Displayer::wasStopped(){
	return Displayer::viewer.wasStopped();
}
