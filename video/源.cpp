#include<opencv2/opencv.hpp>
using namespace cv;
int main()
{
	VideoCapture capture("D:/Ѹ������/[LAC][180200][357][x264_aac][GB][720P].mp4");
	while (1) {
		Mat frame;//�洢ÿһ֡��ͼ��
		capture >> frame;//��ȡ��ǰ�ؼ�֡
		Mat edge, grayimage;
		cvtColor(frame, grayimage, CV_BGR2GRAY);
		//blur(grayimage,edge,Size(3,3));

		//Canny(edge,edge,3,9,3);

		if (frame.empty())
		{
			break;//��ȡ������˳�

		}

		namedWindow("test",WINDOW_NORMAL);
		imshow("test", grayimage);
		waitKey(5);//��ʱ30ms
	}
	return 0;
}
