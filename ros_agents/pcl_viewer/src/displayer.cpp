/*
 * displayer.cpp
 *
 *  Created on: Dec 1, 2013
 *      Author: Iuri Andrade
 */

#include "displayer.h"

Displayer::Displayer()
{
	viewer_ = new pcl::visualization::CloudViewer("Cloud Viewer");
}

Displayer::~Displayer()
{
	delete(viewer_);
}

void Displayer::setDisplayedCloud(CloudXYZ::Ptr &cloud)
{
	viewer_->showCloud(cloud);
	displayed_cloud_ = cloud;
}

CloudXYZ::Ptr Displayer::getDisplayedCloud()
{
	return displayed_cloud_;
}

bool Displayer::wasStopped()
{
	return viewer_->wasStopped();
}
