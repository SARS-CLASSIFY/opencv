#include<opencv2/opencv.hpp>
using namespace cv;
int main()
{
	VideoCapture capture("D:/迅雷下载/[LAC][180200][357][x264_aac][GB][720P].mp4");
	while (1) {
		Mat frame;//存储每一帧的图像
		capture >> frame;//读取当前关键帧
		Mat edge, grayimage;
		cvtColor(frame, grayimage, CV_BGR2GRAY);
		//blur(grayimage,edge,Size(3,3));

		//Canny(edge,edge,3,9,3);

		if (frame.empty())
		{
			break;//读取完毕则退出

		}

		namedWindow("test",WINDOW_NORMAL);
		imshow("test", grayimage);
		waitKey(5);//延时30ms
	}
	return 0;
}
