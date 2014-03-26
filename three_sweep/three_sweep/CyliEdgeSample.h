// 圆柱形目标采样

#ifndef CYLIEDGESAMPLE_H
#define CYLIEDGESAMPLE_H

#include "EdgeSample.h"
#include "library.h"

class CyliEdgeSample: public EdgeSample{
public:
	void init(std::vector<Vector3D> v);
	CyliEdgeSample* getNextEdge();
	void sample();
	void std::vector<Vector3D> getSample();
	void setSampleNum(int num) { sampleNum = num; }

private:
	std::vector<Vector2D> samples;  
	Vector2D center;   
	Vector2D normal;   

	double a;  // two arguments for a ellipse 
	double b;

	static int sampleNum;
	Vector2D getEllipsePoint(int i);
};

int CyliEdgeSample::sampleNum;

#endif