#ifndef OBJ_H
#define OBJ_H

#include <GL/gl.h>
#include <GL/glut.h>

#include "library.h"

class Obj{
public:
	void initScene();
	void draw();
	void insertSample(std::vector<Vector3D> v);

	void setSampleNum(int n) { sampleNum = n;}
	void setHigth(int h) { sceneHight = h;}
	void setWidth(int w) { setWidth = w; }
private:
	void display();
	int sampleNum;
	int sceneHight;
	int sceneWidth;

	std::vector<Triangle> triangles;
	std::vector<Vector3D> topEdge;

	Triangle getTriangle(Vector3D&, Vector3D&, Vector3D&);
};
#endif