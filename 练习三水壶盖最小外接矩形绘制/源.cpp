#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
//转灰度->二值化->闭运算连通->寻找轮廓->读取外接四边形的各点坐标->绘制外接四边形
//原则：二值化后给予尽可能多的轮廓区域,通过特征筛选需要的轮廓区域
int main()
{

	namedWindow("edge", WINDOW_NORMAL);
	namedWindow("srcimg",WINDOW_NORMAL);
	Mat srcimg = imread("1.jpg");
	int height = srcimg.rows;
	int width = srcimg.cols;



	//二值化,由于需要提取区域为红色，所以可以将所有红色像素点区域置位1，其他为0
	Mat binaryimg;  //二值化结果
	//自定义阈值
	double i_minB = 20;
	double i_maxB = 110;
	//0-255
	double i_minG = 20;
	double i_maxG = 100;
	//0-255
	double i_minR = 90;
	double i_maxR = 255;
	cv::inRange(srcimg, Scalar(i_minB, i_minG, i_minR), Scalar(i_maxB, i_maxG, i_maxR), binaryimg);//根据设定多通道阈值进行二值化
	//进行进一步的筛选来消除黑色的类红色区域
	for (int j = 0;j < height;j++) {
		for (int i = 0;i < width;i++) {
			if ((srcimg.at<Vec3b>(j, i)[0] + srcimg.at<Vec3b>(j, i)[1]) >= srcimg.at<Vec3b>(j, i)[2]) {
				binaryimg.at<uchar>(j,i) = 0;
			}

		}

	}



	//形态学操作开运算去噪
	Mat element = getStructuringElement(MORPH_RECT, Size(13, 13));
	Mat openimg;
	morphologyEx(binaryimg, openimg, MORPH_CLOSE, element);//闭运算将细小点联通





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

		if (rbox.size.width >= 50 && rbox.size.height >= 50) {				//简单的长宽特征选择
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