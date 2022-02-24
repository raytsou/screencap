#include <ros/ros.h>
#include <std_msgs/String.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

#include <sstream>

#include <screencap/screencap.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "screencap_node");

  ros::NodeHandle nhtopics("");
  ros::NodeHandle nhparams("~");

  int rate;
  nhparams.param<int>("rate", rate, 1);

  image_transport::ImageTransport it(nhtopics);
  image_transport::Publisher pub = it.advertise("screen/image", 1);
  ScreenCap cap;
  cv::Mat image;
  sensor_msgs::ImagePtr msg;

  ros::Rate loop_rate(rate);
  while (nhtopics.ok()) {
    cap(image);
    msg = cv_bridge::CvImage(std_msgs::Header(), "8UC4", image).toImageMsg();
    pub.publish(msg);
    loop_rate.sleep();
  }
  ros::spin();
  return 0;
}