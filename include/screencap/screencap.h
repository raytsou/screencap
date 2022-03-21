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

class ScreenCap
{
  public:
    ScreenCap();
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
    uint x = 0;
    uint y = 0;
    uint width = 1920;
    uint height = 1080;

    bool init;
};
