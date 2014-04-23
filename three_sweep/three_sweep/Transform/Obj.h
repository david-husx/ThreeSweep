#ifndef OBJ_H
#define OBJ_H

#include "../Basic/Basic.h"
#include <vector>

class Obj{
public:
	void initScene();
	void draw();
	void insertSample(std::vector<Vector3D> v);

	void setSampleNum(int n) { sampleNum = n;}
	void setHigth(int h) { sceneHight = h;}
	void setWidth(int w) { sceneWidth = w; }

	void setTriangle(Triangle &t, Vector3D&, Vector3D&, Vector3D&);

	void debugShow();
private:
	void display();
	int sampleNum;
	int sceneHight;
	int sceneWidth;

	std::vector<Triangle> triangles;
	std::vector<Vector3D> topEdge;
};
#endif