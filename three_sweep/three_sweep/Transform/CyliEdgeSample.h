#ifndef CYLIEDGESAMPLE_H
#define CYLIEDGESAMPLE_H

#include "EdgeSample.h"
#include "../Basic/Basic.h"
#include "Boundary.h"

class CyliEdgeSample: public EdgeSample{
public:
	CyliEdgeSample(){}
	void init(std::vector<Vector2D> v);
	EdgeSample* clone();
	void sample(int flag);

	double getA() { return a; }
	double getB() { return b; }

	void setA(double A) { a = A; }
	void setB(double B) { b = B; }

private:

	double a;  // two arguments for a ellipse 
	double b;

	Vector2D getEllipsePoint(int i);
};

#endif