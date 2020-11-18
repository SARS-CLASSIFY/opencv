#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
//转灰度->二值化->开运算去噪->寻找轮廓
int main()
{
	Mat srcimg = imread("1.jpg");
	Mat grayimg;
	cvtColor(srcimg, grayimg, COLOR_BGR2GRAY);//转灰度图
	grayimg = ~grayimg;//取反转化

	//二值化
	Mat edge;//二值化结果
	threshold(grayimg, edge, 100, 255, CV_THRESH_OTSU);


	//形态学操作开运算去噪
	Mat element = getStructuringElement(MORPH_RECT, Size(7, 7));
	Mat erodeimg;
	morphologyEx(edge, erodeimg, MORPH_OPEN, element);//开运算消除微小点

	//寻找轮廓
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(erodeimg, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);

	
	//历遍所有顶层轮廓，绘制每个组件的颜色
	int index = 0;

	for (;index >= 0;index = hierarchy[index][0]) {
		Scalar color(0, 255,255);//定义填充颜色

		//特征筛选
		//通过最小外接矩形的长宽比以及面积来确定是否为目标连通域
		RotatedRect rbox = minAreaRect(contours[index]);
		if (0.9 <= (rbox.size.width / rbox.size.height) && ( rbox.size.width / rbox.size.height) <= 1.1
			&& (rbox.size.width * rbox.size.height) >= 1900 && (rbox.size.width * rbox.size.height) <= 9000) {
			//cout << rbox.size.width / rbox.size.height <<"   "<< rbox.size.height <<"   "<< rbox.size.width << endl;//用于调参
			drawContours(srcimg, contours, index, color, CV_FILLED, 8, hierarchy);
		}



	}
	
	imshow("edge", edge);
	imshow("srcimg", srcimg);
	waitKey(0);

}