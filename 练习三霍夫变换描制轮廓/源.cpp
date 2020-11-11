#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat midImg;
	Mat src = imread("1.jpg");
	if (src.empty())	return -1;
	//��Ե���ӻҶ�ͼת��
	Canny(src, midImg, 50, 200, 3);

	//���л���任
	std::vector<cv::Vec4i> lines;
	cv::HoughLinesP(midImg, lines, 1, CV_PI / 180, 40,50,10);

	//������ͼ�л��Ƴ�ÿ��ֱ��
	for(size_t i =0;i<lines.size();i++){
		line(src, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(0, 0, 255), 1, LINE_AA);
	}
	imshow("mid", midImg);
	imshow("out", src);
	waitKey(0);
	return 0;

}