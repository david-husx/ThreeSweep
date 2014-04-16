//根据现有的边缘，进行采样，转化为3D坐标后传给OBJ 

#ifndef EDGESAMPLE_H
#define EDGESAMPLE_H

#include "Boundary.h"

class EdgeSample{
public:
	EdgeSample(){

	}
	virtual void init(std::vector<Vector2D>) = 0;   // initlize by user's input. only the first will use this function
	virtual EdgeSample clone() = 0;   // get next EdgeSample 
	virtual std::vector<Vector2D> getSample() = 0;  // return the sample points' coordinates in 2D

	Vector2D getNormal() {  return normal; }
	//virtual void adjustNormal() = 0;
	std::vector<Vector2D> getEndpoint() { return endpoint; }
	//virtual void adjustEndpoint() = 0;
	virtual void sample();  // calculate the sample points' coordinates after adjusting normal and endpoint

	static void setSampleNum(int i) { sampleNum = i; }
	static int getSampleNum() { return sampleNum; }

	void setCenter(Vector2D v) { center = v; }
	void setNormal(Vector2D v) { normal = v; }
	void setEndpoint(std::vector<Vector2D> v) { endpoint[0] = v[0]; endpoint[1] = v[1]; }
	void setBoundary(Boundary* b) { boundary = b; }

	Vector2D getCenter() { return center; }
	Vector2D getNormal() { return normal; }
	std::vector<Vector2D> getEndpoint() { return endpoint; }

private:
	Boundary *boundary;
	static int sampleNum;

	Vector2D center;    
	Vector2D normal;   
	std::vector<Vector2D> endpoint;
};

int EdgeSample::sampleNum = 24;
#endif