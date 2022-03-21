#include <ros/ros.h>
#include <std_msgs/String.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <ros/console.h>

#include <sstream>

#include <screencap/screencap.h>

class ScreenCapNode
{
  public:
    ScreenCapNode(){
      ros::NodeHandle nhtopics("");
      ros::NodeHandle nhparams("~");

      nhparams.param<int>("rate", rate, 1);

      image_transport::ImageTransport it(nhparams);
      image_transport::Publisher pub = it.advertise("image", 1);

      ros::Rate loop_rate(rate);
      while (nhtopics.ok()) {
        cap(image);
        msg = cv_bridge::CvImage(std_msgs::Header(), "8UC4", image).toImageMsg();
        pub.publish(msg);
        loop_rate.sleep();
      }
    }

    void loginfo(const char* msg){
      ROS_INFO("[%s] %s ", node_name.c_str(), msg);
    }

  private:
    int rate;
    std::string node_name = ros::this_node::getName();
    ScreenCap cap;
    cv::Mat image;
    sensor_msgs::ImagePtr msg;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "screencap_node");
  ScreenCapNode screencap;
  ros::spin();
  return 0;
}