#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

#include <screencap/screencap.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "screencap_node");
  ros::NodeHandle nhtopics("");
  ros::NodeHandle nhparams("~");
  screencap::ScreenCap node(nhtopics, nhparams);
  ros::spin();
  return 0;
}