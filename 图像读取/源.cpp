# include <opencv2/opencv.hpp>
# include <iostream>
using  namespace cv;
int main()
{
	Mat srcimg = imread("D:/1.JPG");
	int height = srcimg.rows;
	int width = srcimg.cols;

	for (int j = 0;j < height;j++) {
		for (int i = 0;i < width;i++) {

			//---------ÏñËØ´¦Àí------------//
			uchar average = (srcimg.at<Vec3b>(j, i)[0] + srcimg.at<Vec3b>(j, i)[1] + srcimg.at<Vec3b>(j, i)[2]) / 3;
			srcimg.at<Vec3b>(j, i)[0] = average;
			srcimg.at<Vec3b>(j, i)[1] = average;
			srcimg.at<Vec3b>(j, i)[2] = average;


		}



	}
	namedWindow("test",WINDOW_NORMAL);

	imshow("test",srcimg);
	waitKey(0);
	return 0;

}