#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include "AgentViewer.h"

int main(int argc, char** argv)
{
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

        if (pcl::io::loadPCDFile<pcl::PointXYZ>("../data/pcd_files/table_scene_lms400.pcd", *cloud) == -1) //* load the file
        {
                PCL_ERROR("Couldn't read file test_pcd.pcd \n");
                return (-1);
        }
        std::cout << "Loaded " << cloud->width * cloud->height
                        << " data points from test_pcd.pcd with the following fields: "
                        << std::endl;
/*        for (size_t i = 0; i < cloud->points.size(); ++i)
                std::cout << " " << cloud->points[i].x << " " << cloud->points[i].y
                                << " " << cloud->points[i].z << std::endl;
*/
        AgentViewer v(cloud);
}
//================================================

/*Class test section, (uncomment to test)
#include <boost/thread/thread.hpp>
#include <pcl/common/common_headers.h>
#include <pcl/features/normal_3d.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>
#include "PCDReadWrite.h"

int main(int argc, char** argv)
{
	PCDReadWrite reader;
	reader.read();
	reader.write();
}
*/
