#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
//ת�Ҷ�->��ֵ��->��������ͨ->Ѱ������->��ȡ����ı��εĸ�������->��������ı���
//ԭ�򣺶�ֵ������辡���ܶ����������,ͨ������ɸѡ��Ҫ����������
int main()
{

	namedWindow("edge", WINDOW_NORMAL);
	namedWindow("srcimg",WINDOW_NORMAL);
	Mat srcimg = imread("1.jpg");
	int height = srcimg.rows;
	int width = srcimg.cols;



	//��ֵ��,������Ҫ��ȡ����Ϊ��ɫ�����Կ��Խ����к�ɫ���ص�������λ1������Ϊ0
	Mat binaryimg;  //��ֵ�����
	//�Զ�����ֵ
	double i_minB = 20;
	double i_maxB = 110;
	//0-255
	double i_minG = 20;
	double i_maxG = 100;
	//0-255
	double i_minR = 90;
	double i_maxR = 255;
	cv::inRange(srcimg, Scalar(i_minB, i_minG, i_minR), Scalar(i_maxB, i_maxG, i_maxR), binaryimg);//�����趨��ͨ����ֵ���ж�ֵ��
	//���н�һ����ɸѡ��������ɫ�����ɫ����
	for (int j = 0;j < height;j++) {
		for (int i = 0;i < width;i++) {
			if ((srcimg.at<Vec3b>(j, i)[0] + srcimg.at<Vec3b>(j, i)[1]) >= srcimg.at<Vec3b>(j, i)[2]) {
				binaryimg.at<uchar>(j,i) = 0;
			}

		}

	}



	//��̬ѧ����������ȥ��
	Mat element = getStructuringElement(MORPH_RECT, Size(13, 13));
	Mat openimg;
	morphologyEx(binaryimg, openimg, MORPH_CLOSE, element);//�����㽫ϸС����ͨ





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

		if (rbox.size.width >= 50 && rbox.size.height >= 50) {				//�򵥵ĳ�������ѡ��
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