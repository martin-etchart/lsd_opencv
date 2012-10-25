// Program: lsd_opencv.c
// Proyect: encuadro - Facultad de Ingeniería - UDELAR
// Author: Martin Etchart - mrtn.etchart@gmail.com
//
// Description:
// Line Segment Detector (LSD) 1.6 for segment detection and OpenCV 2.3
// as interface.
// Developed for encuadro project: 
// http://github.com/encuadro/encuadro
//
// Program hosted on:
// http://github.com/martin-etchart/lsd_opencv

#include "opencv/highgui.h"
#include "opencv/cv.h"
#include <stdio.h>
#include <stdlib.h>

#include "lsd.h"

int main( int argc, char** argv){

int i,j;

double fps = 1.0;
CvCapture* capture;
if ( argc == 1 ) {
 	capture = cvCreateCameraCapture (0);
} else {
 	capture = cvCreateFileCapture (argv[1]);
// 	fps = cvGetCaptureProperty(capture, CV_CAP_PROP_FPS); DOES NOT ALWAYS WORK
}
assert( capture != NULL );

//get capture properties
int width  = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
int height = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);

//create OpenCV image structs
IplImage *frame;
IplImage *frameBW = cvCreateImage( cvSize( width, height ), IPL_DEPTH_8U, 1 );
IplImage *frameLSD = cvCreateImage( cvSize( width, height ), IPL_DEPTH_8U, 3 );

//create LSD image type
double *image;
image = (double *) malloc( width * height * sizeof(double) );

while (1) {
    frame = cvQueryFrame( capture );
    if( !frame ) break;

    //convert to grayscale
    cvCvtColor( frame , frameBW, CV_RGB2GRAY);

    //cast into LSD image type
    uchar *data = (uchar *)frameBW->imageData;
    for (i=0;i<width;i++){
    for(j=0;j<height;j++){
        image[ i + j * width ] = data[ i + j * width];
    }
    }

    //run LSD
    double *out;
    int n;
    out = lsd( &n, image, width, height );

    //DO PROCESSING DRAWING ETC

    //draw segments on frame and frameLSD
	cvZero(frameLSD);
    for (j=0; j<n ; j++){       
        //define segment end-points
        CvPoint pt1 = cvPoint(out[ 0 + j * 7 ],out[ 1 + j * 7 ]);
        CvPoint pt2 = cvPoint(out[ 2 + j * 7 ],out[ 3 + j * 7 ]);

        // draw line segment on frame
        cvLine(frame,pt1,pt2,CV_RGB(0,255,0),1.5,8,0);
        cvLine(frameLSD,pt1,pt2,CV_RGB(255,255,255),out[ 5 + j * 7 ],8,0);
	}

    cvShowImage("FRAME WITH LSD",frame);
    cvShowImage("LSD",frameLSD);

    //free memory
    free( (void *) out );

    char c = cvWaitKey(1.0/fps);
    if( c == 27 ) break; // ESC QUITS
}
//free memory
free( (void *) image );

cvDestroyWindow( "FRAME WITH LSD");
cvDestroyWindow( "LSD");

cvReleaseCapture( &capture );
cvReleaseImage( &frame );
cvReleaseImage( &frameBW );
cvReleaseImage( &frameLSD );}
