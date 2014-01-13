/*
 * Filters.h
 *
 *  Created on: Oct 23, 2013
 *      Author: Shehzad Ahmed
 */
#include <pcl/point_types.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include "filters_interface.h"

#ifndef STATISTICALOUTLIERREMOVAL_FILTERS_H_
#define STATISTICALOUTLIERREMOVAL_FILTERS_H_

class StatisticalOutlierFilter : public FiltersInterface
{
public:

	void applyFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest);
	void setNeighbours(int mean_neighbours);
	void setStandardDeviation(float std_dev_thres);

private:
	int neighbours_;
	float stdandard_deviation_;
};

#endif /* STATISTICALOUTLIERREMOVAL_FILTERS_H_ */

