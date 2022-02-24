# Overview

Screencap is a ROS node that captures the output of your screen and outputs it at a given rate. We launch as below

`roslaunch screencap screencap.launch`

 By default, the rate is 50hz. To launch with a different rate, launch using the `rate` arg

 `roslaunch screencap screencap.launch rate:=20` 

# Multiple Screens

The default settings is to capture the top left 1920x1080 pixels of your display arrangement. I'm not certain how to change this and I don't need it yet so figure it out yourself. 

# Performance

I'm using a Ryzen 7 2600X with 64Gb DDR4-3200 cl 16 and a RX 6800XT. The max I can get is about 84 fps but I'm bad at C++ so this number can probably improve.

# Citations

The source code for this node is mostly derived from `scripts/screencap.cpp`. This script is directly copy and pasted from a stack overflow thread found [here](https://stackoverflow.com/a/39781697). This script can be compiled and ran with

```
g++ screencap.cpp -o sc -lX11 -lXext -Ofast -mfpmath=both -march=native -m64 -funroll-loops -mavx2 `pkg-config opencv4 --cflags --libs` && ./sc
```