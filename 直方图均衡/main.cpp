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

	Mat dst;//���ս��ͼ��

	Mat src = imread("example1.jpg");

	if (!src.data) {
		std::cout << "ͼ�����ʧ�ܣ�" << std::endl;
		exit(1);
	}

	//������ͨ����ͼ��
	split(src, channels);
	imageBlueChannel = channels.at(0);
	imageGreenChannel = channels.at(1);
	imageRedChannel = channels.at(2);

	//����ͨ���ֱ����ֱ��ͼ����
	equalizeHist(imageBlueChannel, dstBlueChannel);
	equalizeHist(imageGreenChannel, dstGreenChannel);
	equalizeHist(imageRedChannel, dstRedChannel);
	//�ϳ���ͨ��Ϊ����ͼ��
	channels.at(0) = dstBlueChannel;
	channels.at(1) = dstGreenChannel;
	channels.at(2) = dstRedChannel;

	merge(channels, dst);

	imshow("dst", dst);
	waitKey(0);

	return 0;

}