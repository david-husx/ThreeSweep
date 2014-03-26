//根据现有的边缘，进行采样，转化为3D坐标后传给OBJ 

#ifndef EDGESAMPLE_H
#define EDGESAMPLE_H

#include "2DBoundary.h"

class EdgeSample{
public:
	EdgeSample(){

	}
	virtual void init(std::vector<Vector3D>) = 0;   // initlize by user's input. only the first will use this function
	virtual EdgeSample* getNextEdge() = 0;   // get next EdgeSample 
	virtual std::vector<Vector3D> getSample() = 0;  // return the sample points' coordinates

	Vector2D getNormal() {  return normal; }
	virtual void adjustNormal() = 0;
	Vector2D[] getEndpoint() { return endpoint; }
	virtual void adjustEndpoint() = 0;
	virtual void sample();  // calculate the sample points' coordinates after adjusting normal and endpoint

private:
	Boundary *boundary;
	Vector2D normal;
	Vector2D[2] endpoint;
};
#endif