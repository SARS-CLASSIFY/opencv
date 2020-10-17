/*����ԭͼ->��ȡ�Զ����->���ͼ���ʴ����*/
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat srcimg = imread("C://Users//86150//Desktop//1.jpg");
	Mat grayimg,binaryimg;
	cvtColor(srcimg, grayimg, CV_BGR2GRAY);
	threshold(grayimg, binaryimg, 100, 255, THRESH_OTSU);
	namedWindow("ԭͼ", WINDOW_NORMAL);
	namedWindow("����Ч��ͼ", WINDOW_NORMAL);
	namedWindow("��ʴЧ��ͼ",WINDOW_NORMAL);
	namedWindow("������", WINDOW_NORMAL);
	namedWindow("������", WINDOW_NORMAL);

	Mat element = getStructuringElement(MORPH_RECT,Size(15,15));
	Mat out,out1,out2,out3;//���ͣ���ʴ
	morphologyEx(binaryimg,out, MORPH_ERODE,element);//��ʴ����
	morphologyEx(binaryimg, out1, MORPH_DILATE, element);//��������
	morphologyEx(binaryimg, out2, MORPH_OPEN, element);//������
	morphologyEx(binaryimg, out3, MORPH_CLOSE, element);//������
	imshow("ԭͼ",srcimg);
	imshow("����Ч��ͼ", out1);
	imshow("��ʴЧ��ͼ", out);
	imshow("������", out2);
	imshow("������", out3);

	waitKey(0);

	return 0;
}
