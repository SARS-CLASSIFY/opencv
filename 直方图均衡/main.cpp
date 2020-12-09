#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	std::vector<Mat> channels;
	Mat imageBlueChannel;
	Mat imageGreenChannel;
	Mat imageRedChannel;


	Mat dstBlueChannel;
	Mat dstGreenChannel;
	Mat dstRedChannel;

	Mat dst;//最终结果图像

	Mat src = imread("example1.jpg");

	if (!src.data) {
		std::cout << "图像读入失败！" << std::endl;
		exit(1);
	}

	//分离三通道的图像
	split(src, channels);
	imageBlueChannel = channels.at(0);
	imageGreenChannel = channels.at(1);
	imageRedChannel = channels.at(2);

	//对三通道分别进行直方图均衡
	equalizeHist(imageBlueChannel, dstBlueChannel);
	equalizeHist(imageGreenChannel, dstGreenChannel);
	equalizeHist(imageRedChannel, dstRedChannel);
	//合成三通道为完整图像
	channels.at(0) = dstBlueChannel;
	channels.at(1) = dstGreenChannel;
	channels.at(2) = dstRedChannel;

	merge(channels, dst);

	imshow("dst", dst);
	waitKey(0);

	return 0;

}