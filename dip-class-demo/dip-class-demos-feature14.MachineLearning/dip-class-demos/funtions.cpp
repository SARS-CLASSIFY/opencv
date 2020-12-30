﻿#include "stdafx.h"
#include "funtions.h"
#include "parameters.h"


VideoCapture createInput(bool useCamera, std::string videoPath)
{
	//选择输入
	VideoCapture capVideo;
	if (useCamera) {
		capVideo.open(0);
	}
	else {
		capVideo.open(videoPath);
	}
	return capVideo;
}

void segColor()
{

	//Mat src= imread("../testImages\\movie.jpg");
	VideoCapture read_video =  createInput(0, "../testImages\\dragon.mp4");
	VideoCapture read_video2 = createInput(0, "../testImages\\bg.mp4");
	read_video.set(0,6*1000);//从第6秒开始读
		while (1) {
			Mat frame,frame2;//定义一个MAT变量，用于存储每一帧的图像
			Mat img2;
			read_video >> frame;
			read_video2 >> frame2;

			int width = frame2.cols;
			int height = frame2.rows;
			//Size dsize = Size(width,height);
			//resize(frame, frame, dsize);//匹配大小

			if (frame2.empty()) {
				break;
			}

			Mat mask = Mat::zeros(frame.size(), CV_8UC1);
			createMaskByKmeans(frame, mask);
			

			if (mask.at<uchar>(0, 0) != 0|| mask.at<uchar>(20, 300) != 0) {
				mask = Mat::zeros(frame.size(), CV_8UC1);
			}

			frame.copyTo(img2,mask);

			
			for (int row = 0; row < height; row++) {
				for (int col = 0; col < width; col++) {
					if (img2.at<Vec3b>(row, col)[0] != 0) {
							frame2.at<Vec3b>(row, col)[0] = img2.at<Vec3b>(row, col)[0];
							frame2.at<Vec3b>(row, col)[1] = img2.at<Vec3b>(row, col)[1];
							frame2.at<Vec3b>(row, col)[2] = img2.at<Vec3b>(row, col)[2];
					}
				}
			}

			imshow("src", img2);
			imshow("mask", frame2);

			waitKey(10);
		}
}

int kMeansDemo()
{
	const int MAX_CLUSTERS = 5;//限定五种颜色
	Scalar colorTab[] =
	{
		Scalar(0, 0, 255),
		Scalar(0,255,0),
		Scalar(255,100,100),
		Scalar(255,0,255),
		Scalar(0,255,255)
	};

	Mat img(500, 500, CV_8UC3);
	RNG rng(12345);//随机生成类

	for (;;)
	{
		int k, clusterCount = rng.uniform(2, MAX_CLUSTERS + 1);
		int i, sampleCount = rng.uniform(1, 1001);
		Mat points(sampleCount, 1, CV_32FC2), labels;

		clusterCount = MIN(clusterCount, sampleCount);
		std::vector<Point2f> centers;

		/* generate random sample from multigaussian distribution */
		for (k = 0; k < clusterCount; k++)
		{
			Point center;
			center.x = rng.uniform(0, img.cols);
			center.y = rng.uniform(0, img.rows);
			Mat pointChunk = points.rowRange(k*sampleCount / clusterCount,
				k == clusterCount - 1 ? sampleCount :
				(k + 1)*sampleCount / clusterCount);
			rng.fill(pointChunk, RNG::NORMAL, Scalar(center.x, center.y), Scalar(img.cols*0.05, img.rows*0.05));
		}

		randShuffle(points, 1, &rng);

		double compactness = kmeans(points, clusterCount, labels,
			TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0),
			3, KMEANS_PP_CENTERS, centers);

		img = Scalar::all(0);

		for (i = 0; i < sampleCount; i++)
		{
			int clusterIdx = labels.at<int>(i);
			Point ipt = points.at<Point2f>(i);
			circle(img, ipt, 2, colorTab[clusterIdx], FILLED, LINE_AA);
		}
		for (i = 0; i < (int)centers.size(); ++i)
		{
			Point2f c = centers[i];
			circle(img, c, 40, colorTab[i], 1, LINE_AA);
		}
		cout << "Compactness: " << compactness << endl;

		imshow("clusters", img);

		char key = (char)waitKey();
		if (key == 27 || key == 'q' || key == 'Q') // 'ESC'
			break;
	}

	return 0;
}

int createMaskByKmeans(cv::Mat src, cv::Mat & mask)
{
	if (	(mask.type() != CV_8UC1)
		||	(src.size() != mask.size())
		) {
		return 0;
	}

	int width = src.cols;
	int height = src.rows;

	int pixNum = width * height;
	int clusterCount = 2;
	Mat labels;
	Mat centers;

	//制作kmeans用的数据
	Mat sampleData = src.reshape(3, pixNum);
	Mat km_data;
	sampleData.convertTo(km_data, CV_32F);

	//执行kmeans
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);
	kmeans(km_data, clusterCount, labels, criteria, clusterCount, KMEANS_PP_CENTERS, centers);

	//制作mask
	uchar fg[2] = { 0,255 };
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			mask.at<uchar>(row, col) = fg[labels.at<int>(row*width+col)];
		}
	}

	return 0;
}