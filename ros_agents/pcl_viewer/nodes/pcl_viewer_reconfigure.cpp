#include <dynamic_reconfigure/server.h>
#include <displayer.h>

void callback(your_package::MyStuffConfig &config, uint32_t level)
{
  ROS_INFO("Reconfigure request : %s", config.viewer_topic_name.viewer_sub.c_str());
  // do nothing for now
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "pcl_viewer_reconfigure_node");
  dynamic_reconfigure::Server<Displayer> srv;
  dynamic_reconfigure::Server<Displayer>::CallbackType f;
  f = boost::bind(&callback, _1, _2);
  srv.setCallback(f);
  ROS_INFO("Starting to spin...");
  ros::spin();
  return 0;
}
