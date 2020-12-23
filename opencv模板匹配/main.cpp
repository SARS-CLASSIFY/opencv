#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main()
{

	Mat frame, tempMat, refMat,resultMat;
	VideoCapture capture(0);
	int cnt = 0;
	while (1) {
		capture >> frame;
		if (cnt == 0) { //��ȡ��һ֡Ϊģ��
			Rect2d r;
			r = selectROI(frame, true);
			tempMat = frame(r);
			tempMat.copyTo(refMat);
			destroyAllWindows;
		}
		//����ģ��ƥ��
		int match_method = 0;
		matchTemplate(frame,refMat,resultMat,match_method);
		//��һ��
		normalize(resultMat, resultMat, 0, 1, NORM_MINMAX, -1, Mat());

		double minVal;
		double maxVal;
		Point minLoc;
		Point maxLoc;
		Point localtion;
		Point matchLoc;
		//Ѱ�Ҽ�ֵ
		minMaxLoc(resultMat, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
		localtion.x = minLoc.x + tempMat.cols;
		localtion.y = minLoc.y + tempMat.rows;
		cv::rectangle(frame, minLoc, localtion, cv::Scalar(0, 255, 0), 5, 8);
		imshow("result", frame);

		cnt++;
		waitKey(30);

	}

	return 0;
}