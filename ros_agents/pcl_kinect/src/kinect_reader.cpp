/*
 * kinect_reader.cpp
 *
 *  Created on: Dec 10, 2013
 *      Author: Iuri Andrade
 */

#include "kinect_reader.h"

KinectReader::KinectReader(){
	cloudUnpublished = false;
	currentCloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new CloudXYZ);
	kinectGrabber = new pcl::OpenNIGrabber();
  if (!kinectGrabber == 0){
		boost::function<void (const CloudXYZ::ConstPtr&)> f = 
				boost::bind(&KinectReader::grabberCallback, this, _1);
    kinectGrabber->registerCallback(f);
    kinectGrabber->start();
	}
}

KinectReader::~KinectReader(){
	if(kinectGrabber->isRunning())
		kinectGrabber->stop();
}

void KinectReader::grabberCallback(const CloudXYZ::ConstPtr &cloud){
	cloudUnpublished = true;
	*currentCloud = *cloud;
}

CloudXYZ::Ptr KinectReader::getCloud(){
	cloudUnpublished = false;
	return currentCloud;
}

bool KinectReader::isCloudUnpublished(){
	return cloudUnpublished;
}

bool KinectReader::isRunning(){
	return kinectGrabber->isRunning();
}
