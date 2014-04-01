#include <iostream>
#include "boundary.h"
//#include "CurveExtraction\CurveExtractionStdafx.h"
#include "CurveExtraction\CmCurveEx.h"

using namespace std;

int main()
{
	Boundary b;
	b.test_getSegmentIntersection();

	//string cImgFile = "data/102943_curve.png";
	//CmCurveEx::edge2vector(cImgFile, true);

	system("pause");
	return 0;
}