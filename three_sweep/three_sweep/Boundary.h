#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "library.h"

class Boundary
{
public:
	void init();
	std::vector<Vector2D> calcIntersection(std::vector<Vector2D> v); 
	bool setCycleGraph(std::vector<std::vector<Vector2D> >);

	//just for debug
	void test_getSegmentIntersection();

private:
	std::vector<std::vector<Vector2D> > edge;
	bool getSegmentIntersection(Hline, Hline, Vector2D&);
};

#endif