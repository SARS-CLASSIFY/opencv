#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
	VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened()) {
		std::cout << "���ܴ����ļ�" << std::endl;
		return -1;
	}
	double fps = cap.get(CAP_PROP_FPS);
	std::cout << "fps" << fps << std::endl;
	while (1) {
		cv::Mat frame;
		bool rsucess = cap.read(frame);
		if (!rsucess) {
			std::cout << "���ܴ���Ƶ�ļ��ж�ȡ" << std::endl;
			break;
		}
		else {
			cv::imshow("myframe", frame);

		}
		waitKey(30);
	}
	return 0;

}