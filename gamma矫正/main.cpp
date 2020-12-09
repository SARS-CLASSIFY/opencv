#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define my_size 256
unsigned char  Lut[my_size];//建立查询表

void creat_Lut(unsigned char *Lut,float fgamma) 
{
	for (int i = 0;i < 256;i++) {//建立数据表
		*(Lut+i) = saturate_cast<uchar>(pow((float)(i / 255.0), fgamma) * 255.0f);
		
	}

}

void MyGammaCorrection(Mat& src, Mat& dst, unsigned char * Lut)//实现gamma变换
{
	CV_Assert(src.data);
	CV_Assert(src.depth() != sizeof(uchar));
	const int channels = dst.channels();
	switch (channels)
	{
		case 1:
		{

			MatIterator_<uchar> it, end;
			for (it = dst.begin<uchar>(), end = dst.end<uchar>(); it != end; it++)
				*it = Lut[(*it)];
			break;
		}
		case 3:
		{

			MatIterator_<Vec3b> it, end;
			for (it = dst.begin<Vec3b>(), end = dst.end<Vec3b>(); it != end; it++)
			{
				(*it)[0] = Lut[((*it)[0])];
				(*it)[1] = Lut[((*it)[1])];
				(*it)[2] = Lut[((*it)[2])];
			}

		break;
		}
	}
}
int main()
{
	creat_Lut(Lut, 1 / 2.2);//建立查找表
	Mat src = imread("example.jpg", CV_8UC1);
	Mat dst;
	src.copyTo(dst);
	MyGammaCorrection(src, dst, Lut);//进行gamma变换
	imshow("dst", dst);
	waitKey(0);
	

	return 0;




}