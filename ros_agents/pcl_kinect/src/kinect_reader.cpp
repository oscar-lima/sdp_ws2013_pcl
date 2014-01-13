/*
 * kinect_reader.cpp
 *
 *  Created on: Dec 10, 2013
 *      Author: Iuri Andrade
 */

#include "kinect_reader.h"

KinectReader::KinectReader()
{
	cloud_unpublished_ = false;
	current_cloud_ = pcl::PointCloud<pcl::PointXYZ>::Ptr(new CloudXYZ);
	kinect_grabber_ = new pcl::OpenNIGrabber();
	if (!kinect_grabber_ == 0)
	{
		boost::function<void (const CloudXYZ::ConstPtr&)> f = 
			boost::bind(&KinectReader::grabberCallback, this, _1);
		kinect_grabber_->registerCallback(f);
		kinect_grabber_->start();
	}
}

KinectReader::~KinectReader()
{
	if(kinect_grabber_->isRunning())
	{
		kinect_grabber_->stop();
	}
}

void KinectReader::grabberCallback(const CloudXYZ::ConstPtr &cloud)
{
	cloud_unpublished_ = true;
	*current_cloud_ = *cloud;
}

CloudXYZ::Ptr KinectReader::getCloud()
{
	cloud_unpublished_ = false;
	return current_cloud_;
}

bool KinectReader::isCloudUnpublished()
{
	return cloud_unpublished_;
}

bool KinectReader::isRunning()
{
	return kinect_grabber_->isRunning();
}
