/************************************************************************/
/*  This software is developed by Ming-Ming Cheng.				        */
/*       Url: http://cg.cs.tsinghua.edu.cn/people/~cmm/                 */
/*  This software is free fro non-commercial use. In order to use this	*/
/*  software for academic use, you must cite the corresponding paper:	*/
/*      Ming-Ming Cheng, Curve Structure Extraction for Cartoon Images, */
/*      in The 5th Joint Conference on Harmonious Human Machine			*/
/*      Environment (HHME), 2009, pp. 13-20.							*/
/************************************************************************/

#include "stdafx.h"
#include "CmCurveEx.h"

int main(int argc, char* argv[])
{
	/*Mat cImg = imread(".\\data\\Cartoon.png", CV_LOAD_IMAGE_GRAYSCALE);*/
//	Mat cImg = imread("D:\\zzhu\\contour\\image\\sketch (1).png", CV_LOAD_IMAGE_GRAYSCALE);
	/*Mat cImg = imread("4.png", CV_LOAD_IMAGE_GRAYSCALE);*/
	/*Mat nImg = imread(".\\data\\Nature.png", CV_LOAD_IMAGE_GRAYSCALE);*/
	/*CV_Assert(cImg.data != NULL && nImg.data != NULL);*/
	string cImgFile = "102943_curve.png";

	CmCurveEx::Demo(cImgFile, true);
//	CmCurveEx::Demo(nImg, false);
	return 0;
}


