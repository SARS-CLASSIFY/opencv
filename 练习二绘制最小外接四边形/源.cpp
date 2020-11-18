#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
//ת�Ҷ�->��ֵ��->������ȥ��->Ѱ������->��ȡ����ı��εĸ�������->��������ı���
//ԭ�򣺶�ֵ������辡���ܶ����������,ͨ������ɸѡ��Ҫ����������
int main()
{
	Mat srcimg = imread("1.jpg");
	Mat grayimg;
	cvtColor(srcimg, grayimg, COLOR_BGR2GRAY);//ת�Ҷ�ͼ

	//��ֵ��
	Mat binaryimg;//��ֵ�����
	threshold(grayimg, binaryimg, 100, 255, CV_THRESH_OTSU);


	//��̬ѧ����������ȥ��
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat openimg;
	morphologyEx(binaryimg, openimg, MORPH_OPEN, element);//����������΢С��

	//Ѱ������
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(openimg, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);


	//�������ж�������������ÿ�������ɸѡ��ʵ����Ӧ�Ĳ���
	int index = 0;//�±�



	for (;index >= 0;index = hierarchy[index][0]) {
		Scalar color(0, 0, 255);//���������ɫ(��ɫ)

		//����ɸѡ
		//ͨ����С��Ӿ��εĳ�����Լ������ȷ���Ƿ�ΪĿ����ͨ��
		RotatedRect rbox = minAreaRect(contours[index]);
		cv::Point2f vtx[4];
		rbox.points(vtx);//����������С����ı��εĸ���������������ά����

		if (rbox.size.width >= 50 && rbox.size.height >= 50) {
			cout << rbox.size.width / rbox.size.height << "   " << rbox.size.height << "   " << rbox.size.width << endl;//���ڵ���
			

			//������С����ı��εĻ���
			for (int i = 0;i < 4;i++) {
				cv::line(srcimg, vtx[i], vtx[i < 3 ? i + 1 : 0], color, 2, CV_AA);
			
			}

		}



	}

	imshow("edge", binaryimg);
	imshow("srcimg", srcimg);
	waitKey(0);

}