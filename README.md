lsd_opencv
==========

LSD 1.6 with OpenCv as interface.

LSD is a “linear-time Line Segment Detector giving subpixel accurate results. It is designed to work on any digital image without parameter tuning.”

Complete documentation and source code for the LSD algorithm can be found here:
http://www.ipol.im/pub/art/2012/gjmr-lsd/

I developed a sample application to show how to use LSD with OpenCV as interface.

The code captures from camera/video file and converts form OpenCV IplImage type to the image type needed to use LSD. Then runs LSD and draws the segments and displays the frame using OpenCv functions.

All in real time and makefile for linux provided.

The source code for the sample application can be found and downloaded here: 
https://github.com/martin-etchart/lsd_opencv

The code was developed within my graduate final project encuadro.
