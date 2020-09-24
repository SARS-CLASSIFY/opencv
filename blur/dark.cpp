#include"dark.h"
using namespace cv;

void dark(Mat* image,uchar level)
{
	int height = image->rows;
	int width = image->cols * image->channels();
	for (int j = 0;j < height;j++) {
		uchar* data = image->ptr<uchar>(j);
		for (int i = 0;i < width; i++ ) {
			data[i] = data[i] / level;
		}

	}
}