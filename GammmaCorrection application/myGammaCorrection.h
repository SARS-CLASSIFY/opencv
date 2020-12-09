#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


unsigned char  Lut[256];//������ѯ��

void creat_Lut(unsigned char* Lut, float fgamma)
{
	for (int i = 0;i < 256;i++) {//�������ݱ�
		*(Lut + i) = saturate_cast<uchar>(pow((float)(i / 255.0), fgamma) * 255.0f);

	}

}

void MyGammaCorrection(Mat& src, Mat& dst, unsigned char* Lut)//ʵ��gamma�任
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