sdp_ws2013_pcl
==============

Software Development Project (WS2013/2014) - PCL Group (Pointcloud library)

About this repository : This repository contains code related to PCL usage, the main idea behind this code is to agentify the components of the PCL library and at the same time construct and develop a useful pointcloud program.

It contains both ros independant and ros dependant code, using ROS hydro and PCL 1.7 standalone version.


SDP_PCL setup
=============

Documentation for installation avilable at:

		http://www.openni.org/
		http://pointclouds.org/downloads/linux.html

This steps were tested on kubuntu 12.10 and also there is knowledge about they work on ubuntu 12.04 LTS.
Other Linux distributions might try this code as well but there is no available tests.

1. install openni drivers (for kinect)

		Since pcl 1.7 openni drivers come with PCL library so you don't need to install them

2. install pcl 1.7

		sudo add-apt-repository ppa:v-launchpad-jochen-sprickerhof-de/pcl
		sudo apt-get update
		sudo apt-get install libpcl-all

3. Install cmake

		sudo apt-get install cmake

4. Install gcc (c gnu compiler)

		sudo apt-get install gcc

5. Install essential packages (g++ and others)

		sudo apt-get install build-essential

6. Install and configure github

Create github account:

		https://github.com/

install git:

		sudo apt-get install git

configure git, (start from "setup git" section)

		https://help.github.com/articles/set-up-git

setup ssh keys:

		https://help.github.com/articles/generating-ssh-keys

7. Install ROS hydro

		http://wiki.ros.org/hydro/Installation/Ubuntu

8. Configure bashrc and create proper directories to clone the repository

make proper directories and compile

		mkdir -p ~/ros_ws/sdp_pcl_ws/src
		cd ~/ros_ws/sdp_pcl_ws/src
		catkin_init_workspace
		cd ..
		catkin_make

edit bashrc

		cd ~
		gedit .bashrc

add the following lines at the bottom

		#:::::::::ROS_PCL_BASHRC_CONFIGURATION
		source /opt/ros/hydro/setup.bash
		source ~/ros_ws/sdp_pcl_ws/devel/setup.bash

source your bashrc

		source ~/.bashrc

9. clone the sdp_pcl repository

		cd ~/ros_ws/sdp_pcl_ws/src
		git clone git@github.com:mas-group/sdp_ws2013_pcl.git

10. Compile

		cd ~/ros_ws/sdp_pcl_ws
		catkin_make

You should be able to compile now with no errors.

done! you can now test your installation.


Testing sdp_pcl installation
============================

1. try the kinect simple example

Connect a Microsoft kinnect to your computer.

Compile and run the example:

		cd ~/ros_ws/sdp_pcl_ws/src/sdp_ws2013_pcl/independent_of_ros/examples/kinect_io
		mkdir build && cd build
		cmake ..
		make
		./openni_grabber

Now you should be able to see live pointclouds streaming from kinect.

2. try some other ros_independant pcl examples.

You can do the same procedure in general for running all ros independant examples

a. go to the location of the example

		cd ~/ros_ws/sdp_pcl_ws/src/sdp_ws2013_pcl/independent_of_ros/examples/
		cd example_that_you_want_to_try

b. create build folder and change to that location

		mkdir build && cd build

c. cmake

		cmake ..

You should see something like this:

		Build files have been written to: ~/ros_ws/sdp_pcl_ws/src...

d. make

		make

You should now be able to compile without errors

e. run

Change to build location folder (from previous step) if not there already...

		cd .../build
		./executable_name

To know the executable_name you can type ./ and then "tab" you will see the suggestions.

Another thing you can do is to open CMakeLists.txt and look for the "add executable" line, it will tell you the executable name.

3. run the main program : pcl_agent (ros dependant)

Connect the kinnect and launch the main project:

		roslaunch pcl_agents pcl_agents.launch

By now all the nodes should launch and a gui should show up in the screen waiting for commands (reconfigure parameters).

Now we will see how to use the gui.

4. Usage of the main program : pcl_agent

The project uses ROS and dynamic reconfigure, to use it you must create pipelines during runtime.

To create a pipeline you must specify subscribers, the publishers are fixed.

We have two available pointcloud input sources: read from file and read from depth camera (kinnect).

kinnect is publishing on the topic: /pcl_kinect/output_cloud

So for example to create a simple pipeline to visualize the kinnect we will just make the pcl_viewer to subscribe to that topic.

This can be done by clicking on the left side of the gui on "pcl_viewer", and then write inside "viewer sub" the following:

		/pcl_kinect/output_cloud

Similarly if we want to downsample the cloud first before visualizing it, we can make the proper connections.


Topics info:
----------------------------------------------------------------------------

input :

- pcd file reader : /pcl_file_reader/output_cloud

- depth camera : /pcl_kinect/output_cloud

filters :

- statistical outlier : /statisticaloutlierremoval_filter/output_cloud

- downsampling : /donwsampling_filter/output_cloud

- passtrough : /passtrough_filter/output_cloud

output :

- viewer : does not apply

---------------------------------------------------------------------------

If you have questions you can contact the developers with the subject [PCL_HELP] at:


Oscar Lima: 	olima_84@yahoo.com

Shehzad Ahmed: 	shehzi001@gmail.com

Iuri Andrade:	iuriandrade@yahoo.com.br


Enjoy!


Credits
=======

This project was part of a development of the university:

Hochschule Bonn Rhein Sieg

under the supervision of:

Prof. Dr. Eng. Gerard Kraetzchmar

Teacher Assistant: Ms.C. Frederik Hegger

for the subject: Software Development Project

Thanks.