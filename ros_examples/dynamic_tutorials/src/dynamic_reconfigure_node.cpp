#include <dynamic_reconfigure/server.h>
#include <dynamic_tutorials/MyStuffConfig.h>

void callback(dynamic_tutorials::MyStuffConfig &config, uint32_t level)
{
  ROS_INFO("Reconfigure request : %f %f %i %i %i %s %i %s %f %i",
           config.groups.angles.min_ang, config.groups.angles.max_ang,
           (int)config.intensity, config.cluster, config.skip, 
           config.port.c_str(),(int)config.calibrate_time, 
           config.frame_id.c_str(), config.time_offset,   
           (int)config.allow_unsafe_settings);
  
  // do nothing for now
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "dynamic_reconfigure_node");
  dynamic_reconfigure::Server<dynamic_tutorials::MyStuffConfig> srv;
  dynamic_reconfigure::Server<dynamic_tutorials::MyStuffConfig>::CallbackType f;
  f = boost::bind(&callback, _1, _2);
  srv.setCallback(f);
  ROS_INFO("Starting to spin...");
  ros::spin();
  return 0;
}

