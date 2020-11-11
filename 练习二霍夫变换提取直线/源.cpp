#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat midImg;
	Mat src = imread("1.jpg");
	if (src.empty())	return -1;
	//边缘检测加灰度图转换
	Canny(src, midImg, 50, 200, 3);
	
	//进行霍夫变换
	std::vector<cv::Vec2f> lines;
	cv::HoughLines(midImg, lines, 1, CV_PI / 180,100);

	//依次在图中绘制出每条直线
	std::vector<cv::Vec2f>::iterator it = lines.begin();
	for (;it != lines.end();++it) {
		float rho = (*it)[0], theta = (*it)[1];
		cv::Point pt1, pt2;
		double a = cos(theta);
		double b = sin(theta);
		double x0 = a * rho;
		double y0 = b * rho;
		pt1.x = cv::saturate_cast<int>(x0 + 1000 * (-b));
		pt1.y = cv::saturate_cast<int>(y0 + 1000 * (a));
		pt2.x = cv::saturate_cast<int>(x0 - 1000 * (-b));
		pt2.y = cv::saturate_cast<int>(y0 - 1000 * (a));
		cv::line(src, pt1, pt2, cv::Scalar(0, 0, 255), 1, CV_AA);

	}
	imshow("mid", midImg);
	imshow("out", src);
	waitKey(0);
	return 0;

}