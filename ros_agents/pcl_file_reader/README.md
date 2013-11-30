pcl_file_reader node
====================

commands to test the node:

		roscore
		rosrun pcl_file_reader pcl_file_rear
		rosrun pcl_viewer pcl_viewer
		rostopic pub /read_request std_msgs/String "Read pcd"
		
to change parameters from terminal:

		rosparam set /pcd_path /home/oscar/
		rosparam set /pcd_filename kitchen.pcd
