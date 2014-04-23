#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "../CurveExtraction/CmCurveEx.h"
#include "../Basic/Basic.h"

/***********************************************************************
* This class is used to find exact boundary
* Author: Hu Sixing
* Date  : mar. 26th. 2014
************************************************************************/
class Boundary
{
public:
	Boundary();
	Boundary(const std::string &imgName);

	void init(const std::string &imgName);
	std::vector<Vector2D> calcIntersection(std::vector<Vector2D> v); 
	bool setCycleGraph(std::vector<std::vector<Vector2D> >);

	//just for debug
	void test_getSegmentIntersection(string);

private:
	std::vector<std::vector<Vector2D> > edge;
	bool getSegmentIntersection(Hline, Hline, Vector2D&);
	Mat test_img;
};

#endif