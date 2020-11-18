#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
//ת�Ҷ�->��ֵ��->������ȥ��->Ѱ������
int main()
{
	Mat srcimg = imread("1.jpg");
	Mat grayimg;
	cvtColor(srcimg, grayimg, COLOR_BGR2GRAY);//ת�Ҷ�ͼ
	grayimg = ~grayimg;//ȡ��ת��

	//��ֵ��
	Mat edge;//��ֵ�����
	threshold(grayimg, edge, 100, 255, CV_THRESH_OTSU);


	//��̬ѧ����������ȥ��
	Mat element = getStructuringElement(MORPH_RECT, Size(7, 7));
	Mat erodeimg;
	morphologyEx(edge, erodeimg, MORPH_OPEN, element);//����������΢С��

	//Ѱ������
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(erodeimg, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);

	
	//�������ж�������������ÿ���������ɫ
	int index = 0;

	for (;index >= 0;index = hierarchy[index][0]) {
		Scalar color(0, 255,255);//���������ɫ

		//����ɸѡ
		//ͨ����С��Ӿ��εĳ�����Լ������ȷ���Ƿ�ΪĿ����ͨ��
		RotatedRect rbox = minAreaRect(contours[index]);
		if (0.9 <= (rbox.size.width / rbox.size.height) && ( rbox.size.width / rbox.size.height) <= 1.1
			&& (rbox.size.width * rbox.size.height) >= 1900 && (rbox.size.width * rbox.size.height) <= 9000) {
			//cout << rbox.size.width / rbox.size.height <<"   "<< rbox.size.height <<"   "<< rbox.size.width << endl;//���ڵ���
			drawContours(srcimg, contours, index, color, CV_FILLED, 8, hierarchy);
		}



	}
	
	imshow("edge", edge);
	imshow("srcimg", srcimg);
	waitKey(0);

}