#include "EdgeExtraction.h"

using namespace cv;

EdgeExtraction::EdgeExtraction()
{
}

Mat EdgeExtraction::extract(const Mat& src)
{
	return extract(src, 100, 250, 3);
}

Mat EdgeExtraction::extract(const Mat& src, int para1, int para2, int para3)
{
	Mat dst;
	IplImage *srcImg;
	srcImg = cvCreateImage(cvSize(src.cols, src.rows), 8, 1);
	srcImg->imageData = (char*)src.data;
	IplImage *dstCanny = cvCreateImage(cvGetSize(srcImg), IPL_DEPTH_8U, 1);
	
	cvCanny(srcImg, dstCanny, para1, para2, para3);
	dst = dstCanny;
	
	return dst;
}
