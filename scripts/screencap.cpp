// g++ screencap.cpp -o sc -lX11 -lXext -Ofast -mfpmath=both -march=native -m64 -funroll-loops -mavx2 `pkg-config opencv4 --cflags --libs` && ./sc
#include <opencv2/opencv.hpp>  // This includes most headers!

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XShm.h>

#include <sys/ipc.h>
#include <sys/shm.h>


#include <time.h>
#define FPS(start) (CLOCKS_PER_SEC / (clock()-start))


struct ScreenShot{
  ScreenShot(uint x, uint y, uint width, uint height):
         x(x), y(y), width(width), height(height){

    display = XOpenDisplay(nullptr);
    root = DefaultRootWindow(display);

    XGetWindowAttributes(display, root, &window_attributes);
    screen = window_attributes.screen;
    ximg = XShmCreateImage(display, DefaultVisualOfScreen(screen), DefaultDepthOfScreen(screen), ZPixmap, NULL, &shminfo, width, height);

    shminfo.shmid = shmget(IPC_PRIVATE, ximg->bytes_per_line * ximg->height, IPC_CREAT|0777);
    shminfo.shmaddr = ximg->data = (char*)shmat(shminfo.shmid, 0, 0);
    shminfo.readOnly = False;
    if(shminfo.shmid < 0)
      puts("Fatal shminfo error!");;
    Status s1 = XShmAttach(display, &shminfo);
    printf("XShmAttach() %s\n", s1 ? "success!" : "failure!");

    init = true;
  }

  void operator() (cv::Mat& cv_img){
    if(init)
      init = false;

    XShmGetImage(display, root, ximg, 0, 0, 0x00ffffff);
    cv_img = cv::Mat(height, width, CV_8UC4, ximg->data);
  }

  ~ScreenShot(){
    if(!init)
      XDestroyImage(ximg);

    XShmDetach(display, &shminfo);
    shmdt(shminfo.shmaddr);
    XCloseDisplay(display);
  }

  Display* display;
  Window root;
  XWindowAttributes window_attributes;
  Screen* screen;
  XImage* ximg;
  XShmSegmentInfo shminfo;

  int x, y, width, height;

  bool init;
};


int main(){
  ScreenShot screen(0, 0, 1920, 1080);
  cv::Mat img;

  while(true){
    double start = clock();

    screen(img);

    cv::imshow("img", img);
    printf("fps %4.f  spf %.4f\n", FPS(start), 1 / FPS(start));
    if (cv::waitKey(1) == 27) break;

  }
}