/*����ԭͼ->��ȡ�Զ����->���ͼ���ʴ����*/
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat srcimg = imread("D://1.jpg");

	namedWindow("ԭͼ", WINDOW_NORMAL);
	namedWindow("����Ч��ͼ", WINDOW_NORMAL);
	namedWindow("��ʴЧ��ͼ",WINDOW_NORMAL);
	namedWindow("������", WINDOW_NORMAL);
	namedWindow("������", WINDOW_NORMAL);

	Mat element = getStructuringElement(MORPH_RECT,Size(15,15));
	Mat out,out1,out2,out3;//���ͣ���ʴ
	morphologyEx(srcimg,out, MORPH_ERODE,element);//��ʴ����
	morphologyEx(srcimg, out1, MORPH_DILATE, element);//��������
	morphologyEx(srcimg, out2, MORPH_OPEN, element);//������
	morphologyEx(srcimg, out3, MORPH_CLOSE, element);//������
	imshow("ԭͼ",srcimg);
	imshow("����Ч��ͼ", out1);
	imshow("��ʴЧ��ͼ", out);
	imshow("������", out2);
	imshow("������", out3);

	waitKey(0);

	return 0;
}
