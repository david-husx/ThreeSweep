#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "library.h"

/***********************************************************************
* This class is used to find exact boundary
* Author: Hu Sixing
* Date  : Mar. 26th. 2014
************************************************************************/
class Boundary
{
public:
	void init(const std::string &imgName);
	std::vector<Vector2D> calcIntersection(std::vector<Vector2D> v); 
	bool setCycleGraph(std::vector<std::vector<Vector2D> >);

	//just for debug
	void test_getSegmentIntersection();

private:
	std::vector<std::vector<Vector2D> > edge;
	bool getSegmentIntersection(Hline, Hline, Vector2D&);
};

#endif