

#include "statisticaloutlierremoval_filter.h"


void StatisticalOutlierFilter::applyFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest)
{
		// Create the filtering object
		pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
		sor.setInputCloud (src);
		sor.setMeanK(neighbours_);
		sor.setStddevMulThresh(stdandard_deviation_);
		sor.filter(*dest);
}

void StatisticalOutlierFilter::setNeighbours(int mean_neighbours)
{
	neighbours_ = mean_neighbours;
}

void StatisticalOutlierFilter::setStandardDeviation(float std_dev_thres)
{
	stdandard_deviation_ = std_dev_thres;
}

