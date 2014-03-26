#include "Obj.h"

void Obj::display(){
	
}

void Obj::initScene(){
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(sceneWidth, sceneHight);
	glutCreateWindow("show");
	glutDisplayFunction(display);
}

