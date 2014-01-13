/*
 * kinect_reader.h
 *
 *  Created on: Dec 10, 2013
 *      Author: Iuri Andrade
 */

#ifndef KINECT_READER_H_
#define KINECT_READER_H_

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/openni_grabber.h>

typedef pcl::PointCloud<pcl::PointXYZ> CloudXYZ;

class KinectReader
{
public:
	KinectReader();
	~KinectReader();
	void grabberCallback(const CloudXYZ::ConstPtr &cloud);
	CloudXYZ::Ptr getCloud();
	bool isCloudUnpublished();
	bool isRunning();
private:
	CloudXYZ::Ptr current_cloud_;
	bool cloud_unpublished_;
	pcl::Grabber *kinect_grabber_;
};

#endif /* KINECT_READER_H_ */
