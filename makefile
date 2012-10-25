# Program: makefile
# Proyect: encuadro - Facultad de Ingeniería - UDELAR
# Author: Martin Etchart - mrtn.etchart@gmail.com
#
# Description:
# Line Segment Detector (LSD) 1.6 for segment detection and OpenCV 2.3 
# as interface.
# Developed for encuadro project: 
# http://github.com/encuadro/encuadro
#
# Program hosted on:
# http://github.com/martin-etchart/lsd_opencv


all: lsd.c lsd.h lsd_opencv.c
	gcc -o lsd_opencv lsd_opencv.c lsd.c -lm `pkg-config --cflags --libs opencv`

