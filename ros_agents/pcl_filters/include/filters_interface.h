/*
 * Author:Shehzad,Iuri,Oscar
 * Date: Nov. 28,2013
 */

class FiltersInterface
{
	public:
		virtual void applyFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr src, pcl::PointCloud<pcl::PointXYZ>::Ptr dest)= 0;
};
