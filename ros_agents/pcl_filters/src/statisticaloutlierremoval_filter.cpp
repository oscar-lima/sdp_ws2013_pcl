

#include "statisticaloutlierremoval_filter.h"


void statisticaloutlierremovalFilter::applyFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest)
{
	// Create the filtering object
		pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
		sor.setInputCloud (src);
		sor.setMeanK(neighbours);
		sor.setStddevMulThresh(stdandard_deviation);
		sor.filter(*dest);	
}
	
void statisticaloutlierremovalFilter::setNeighbours(int mean_neighbours)
{
	neighbours = mean_neighbours;
}

void statisticaloutlierremovalFilter::setStandardDeviation(float std_dev_thres)
{
	stdandard_deviation = std_dev_thres;
}

