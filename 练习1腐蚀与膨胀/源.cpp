/*载入原图->获取自定义核->膨胀及腐蚀操作*/
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat srcimg = imread("D://1.jpg");

	namedWindow("原图", WINDOW_NORMAL);
	namedWindow("膨胀效果图", WINDOW_NORMAL);
	namedWindow("腐蚀效果图",WINDOW_NORMAL);
	namedWindow("开运算", WINDOW_NORMAL);
	namedWindow("闭运算", WINDOW_NORMAL);

	Mat element = getStructuringElement(MORPH_RECT,Size(15,15));
	Mat out,out1,out2,out3;//膨胀，腐蚀
	morphologyEx(srcimg,out, MORPH_ERODE,element);//腐蚀运算
	morphologyEx(srcimg, out1, MORPH_DILATE, element);//膨胀运算
	morphologyEx(srcimg, out2, MORPH_OPEN, element);//开运算
	morphologyEx(srcimg, out3, MORPH_CLOSE, element);//开运算
	imshow("原图",srcimg);
	imshow("膨胀效果图", out1);
	imshow("腐蚀效果图", out);
	imshow("开运算", out2);
	imshow("闭运算", out3);

	waitKey(0);

	return 0;
}
