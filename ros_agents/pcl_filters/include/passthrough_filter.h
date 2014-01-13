/*
 * Filters.h
 *
 *  Created on: Oct 23, 2013
 *      Author: Shehzad Ahmed
 */
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include "filters_interface.h"


#ifndef PASSTHROUGH_FILTERS_H_
#define PASSTHROUGH_FILTERS_H_

class PassthroughFilter : public FiltersInterface
{
	struct RangeAxis
	{
		float max_x;
		float min_x;
		float max_y;
		float min_y;
		float max_z;
		float min_z;
	};
	public:
		void applyFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest);
		void setFilterAxis(std::string filter_axis);
		void setMinRange(float range_min);
		void setMaxRange(float range_max);
		void cloudRangesFind(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
	private:
		std::string filter_axis_;
		float range_min_limit_;
		float range_max_limit_;
};

#endif /* PASSTHROUGH_FILTERS_H_ */

