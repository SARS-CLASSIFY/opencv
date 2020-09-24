# include <opencv2/opencv.hpp>
# include <iostream>
using  namespace cv;
int main()
{
	Mat srcM = imread("D:/1.JPG");
	Mat deepMat, shallowMat;
	int height = srcM.rows;
	int width = srcM.cols;

	shallowMat = srcM;
	srcM.copyTo(deepMat);
	
	for (int j = 0;j < height;j++) {
		for (int i = 0;i < width;i++) {

			//---------ÏñËØ´¦Àí------------//
			uchar average = (srcM.at<Vec3b>(j, i)[0] + srcM.at<Vec3b>(j, i)[1] + srcM.at<Vec3b>(j, i)[2]) / 3;
			srcM.at<Vec3b>(j, i)[0] = average;
			srcM.at<Vec3b>(j, i)[1] = average;
			srcM.at<Vec3b>(j, i)[2] = average;


		}



	}
	namedWindow("test",WINDOW_NORMAL);
	namedWindow("test1", WINDOW_NORMAL);
	namedWindow("test2", WINDOW_NORMAL);


	imshow("test",srcM);
	imshow("test1",shallowMat);
	imshow("test2",deepMat);
	waitKey(0);
	return 0;

}