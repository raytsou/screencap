#include <memory>
#include <sstream>
#include <string>
#include <opencv2/core/mat.hpp>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XShm.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <ros/ros.h>


#include <screencap/screencap.h>

namespace screencap {

  class OuterLoopROS
  {
  public:
    ScreenCap(const ros::NodeHandle& nh, const ros::NodeHandle& nhp);
    ~ScreenCap();
    void operator() (cv::Mat& img);

  private:
    ros::NodeHandle nh_, nhp_;
    ros::Publisher pub;

    Display* display;
    Window root;
    XWindowAttributes window_attributes;
    Screen* screen;
    XImage* ximg;
    XShmSegmentInfo shminfo;

    int x, y, width, height;

    bool init;
  };

}
