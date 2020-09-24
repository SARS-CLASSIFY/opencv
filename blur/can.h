#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

void canny_test(Mat img)
{
	Mat edge, grayimage;
	cvtColor(img, grayimage,CV_BayerRG2GRAY);//转化为2灰度值
	blur(grayimage,edge,Size(3,3));//降噪处理

	Canny(edge, edge, 3, 9, 3);
	namedWindow("test",WINDOW_NORMAL);
	imshow("test", edge);
	waitKey(0);

}


