pcl_file_reader node
====================

run all nodes by using provided launch file to test the reader node:

		roslaunch pcl_file_reader load_cloud.launch
		
test by publishing on /read_request topic

		rostopic pub /read_request std_msgs/String "Read pcd"

to run nodes separately:

		roscore
		rosrun pcl_file_reader pcl_file_reader
		rosrun pcl_viewer pcl_viewer
		rostopic pub /read_request std_msgs/String "Read pcd"
		
to change parameters from terminal:

		rosparam set /pcd_path /home/oscar/
		rosparam set /pcd_filename kitchen.pcd
