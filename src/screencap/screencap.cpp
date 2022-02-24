#include <screencap/screencap.h>

ScreenCap::ScreenCap(){
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

  init = s1;
}

void ScreenCap::operator() (cv::Mat& cv_img){
  if(init)
    init = false;

  XShmGetImage(display, root, ximg, 0, 0, 0x00ffffff);
  cv_img = cv::Mat(height, width, CV_8UC4, ximg->data);
}

ScreenCap::~ScreenCap(){
  if(!init)
    XDestroyImage(ximg);

  XShmDetach(display, &shminfo);
  shmdt(shminfo.shmaddr);
  XCloseDisplay(display);
}