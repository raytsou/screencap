#include <rclcpp/rclcpp.hpp>
// #include <std_msgs/msg/string.hpp>
#include <std_msgs/msg/header.hpp>
// #include <sensor_msgs/msg/image.hpp>
#include <image_transport/image_transport.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
// #include <ros/console.h>

#include <sstream>

#include <screencap/screencap.h>

class ScreenCapNode : public rclcpp::Node
{
protected:
  rclcpp::Node::SharedPtr node_handle_;
  image_transport::ImageTransport it;
  image_transport::Publisher pub;
  int rate;
  std::string node_name = this->get_name();
  ScreenCap cap;
  cv::Mat image;
  sensor_msgs::msg::Image::SharedPtr msg;

public:
  ScreenCapNode() :
    Node("screencap_node"),
    // create the shared_ptr node handle for this node.
    node_handle_(std::shared_ptr<ScreenCapNode>(this, [](auto *) {})),
    it(node_handle_),
    pub(it.advertise("image", 10))
  {
    // this->declare_parameter("rate", 1);
    // rate = this->get_parameter("rate").get_parameter_value().get<int>();

    // // image_transport::ImageTransport it(this);
    // // image_transport::Publisher pub = it.advertise("image", 1);

    // // timer_ = this->create_wall_timer((1000.0/(float)rate)ms, std::bind(&ScreenCapNode::publish, this));
    // rclcpp::WallRate loop_rate(rate);
    // while (rclcpp::ok()) {
    //   cap(image);
    //   msg = cv_bridge::CvImage(std_msgs::Header(), "8UC4", image).toImageMsg();
    //   pub.publish(msg);
    //   loop_rate.sleep();
    // }
  }
};
  // void loginfo(const char* msg){
  //   ROS_INFO("[%s] %s ", node_name.c_str(), msg);
  // }



// class ScreenCapNode : public rclcpp::Node
// {
//   ...
// public:
//     ScreenCapNode() :
//       Node("screencap_node"),
//       // create the shared_ptr node handle for this node.
//       node_handle_(std::shared_ptr<ScreenCapNode>(this, [](auto *) {})),
//       it(node_handle_),
//       pub(image_transport.advertise("image", 10)
//     {
//         ....
//     }
//     void (const cv::Mat& frame)
//     {
//         sensor_msgs::msg::Image msg;
//         ....
//         image_publisher_->publish(msg);
//     }
// }


int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ScreenCapNode>());
  rclcpp::shutdown();
  return 0;
}
