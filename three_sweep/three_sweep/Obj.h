#ifndef OBJ_H
#define OBJ_H

#include <GL/gl.h>
#include <GL/glut.h>

class Obj{
public:
	void initScene();
	void draw();
	void insertSample(std::vector<Vector3D> v);
private:
	void display();
	int sampleNum;
	int sceneHight;
	int sceneWidth;
};
#endif