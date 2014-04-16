// 圆柱形目标采样

#ifndef CYLIEDGESAMPLE_H
#define CYLIEDGESAMPLE_H

#include "EdgeSample.h"
#include "library.h"

class CyliEdgeSample: public EdgeSample{
public:
	CyliEdgeSample(){}
	void init(std::vector<Vector3D> v);
	CyliEdgeSample clone();
	void sample();
	std::vector<Vector2D> getSample(){ return samples; }

	double getA() { return a; }
	double getB() { return b; }

	void setA(double A) { a = A; }
	void setB(double B) { b = B; }

	void clear(){ samples.clear(); }

	std::vector<Vector2D> samples;  
private:

	double a;  // two arguments for a ellipse 
	double b;

	Vector2D getEllipsePoint(int i);
};

#endif