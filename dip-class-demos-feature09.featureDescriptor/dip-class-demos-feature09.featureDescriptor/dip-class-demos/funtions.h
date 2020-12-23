#pragma once
#include <opencv2/opencv.hpp>
using namespace cv;

int compareImages();
int calcHOG(cv::Mat src,float * hist,int nAngle,int cellSize);
float normL2(float * Hist1,float *Hist2,int size);

int detectPeople();

int harrisDetector();


