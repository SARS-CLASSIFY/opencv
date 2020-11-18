#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
//转灰度->二值化->开运算去噪->寻找轮廓->读取外接四边形的各点坐标->绘制外接四边形
//原则：二值化后给予尽可能多的轮廓区域,通过特征筛选需要的轮廓区域
int main()
{
	Mat srcimg = imread("1.jpg");
	Mat grayimg;
	cvtColor(srcimg, grayimg, COLOR_BGR2GRAY);//转灰度图

	//二值化
	Mat binaryimg;//二值化结果
	threshold(grayimg, binaryimg, 100, 255, CV_THRESH_OTSU);


	//形态学操作开运算去噪
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat openimg;
	morphologyEx(binaryimg, openimg, MORPH_OPEN, element);//开运算消除微小点

	//寻找轮廓
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(openimg, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);


	//历遍所有顶层轮廓，查找每个组件，筛选并实现相应的操作
	int index = 0;//下标



	for (;index >= 0;index = hierarchy[index][0]) {
		Scalar color(0, 0, 255);//定义填充颜色(红色)

		//特征筛选
		//通过最小外接矩形的长宽比以及面积来确定是否为目标连通域
		RotatedRect rbox = minAreaRect(contours[index]);
		cv::Point2f vtx[4];
		rbox.points(vtx);//将轮廓的最小外接四边形的各个点的坐标存入四维向量

		if (rbox.size.width >= 50 && rbox.size.height >= 50) {
			cout << rbox.size.width / rbox.size.height << "   " << rbox.size.height << "   " << rbox.size.width << endl;//用于调参
			

			//进行最小外接四边形的绘制
			for (int i = 0;i < 4;i++) {
				cv::line(srcimg, vtx[i], vtx[i < 3 ? i + 1 : 0], color, 2, CV_AA);
			
			}

		}



	}

	imshow("edge", binaryimg);
	imshow("srcimg", srcimg);
	waitKey(0);

}