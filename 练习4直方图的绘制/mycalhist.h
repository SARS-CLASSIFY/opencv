/***********************************************************************************************
 **brief 直方图计算函数																		   *
 *                                                                                             *
 *																							   *
 * INPUT: srcimg	--	输入图像数组														   *
 *        R			--	R通道直方图计算结果保存数组											   *
 *		  G			--	G通道直方图计算结果保存数组											   *
 *		  B			--  B通道直方图计算结果													   *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   09/30/2020 SRS																			   *
 *=============================================================================================*/

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>
using namespace cv;
using namespace std;

void mycalchist(Mat srcimg, float* R, float* G, float* B) {
	int height = srcimg.rows;
	int width = srcimg.cols;

	int total = height * width;//记录像素总数
	for (int j = 0;j < height;j++) {
		for (int i = 0;i < width;i++) {
			R[srcimg.at<Vec3b>(j, i)[0]] ++;
			B[srcimg.at<Vec3b>(j, i)[1]] ++;
			G[srcimg.at<Vec3b>(j, i)[2]] ++;
		}

	}
	
	for (int m = 0;m < 256;m++) {
		
		R[m] = R[m] / total;
		G[m] = G[m] / total;
		B[m] = B[m] / total;
		//cout << fixed<<setprecision(5)<<R[m]<<' ' <<B[m]<<' '<<G[m]<<endl ;//输出测试

	}
	


}
