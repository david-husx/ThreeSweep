#ifndef _INV_CAMERA_H_
#define _INV_CAMERA_H_

#include "..\Basic\Basic.h"
#include <vector>

class InvCamera
{
public:
	InvCamera(int, int, double, double, double);

	std::vector<Vector3D> calcAxes(double*, double*);
	std::vector<Vector3D> twoDtothreeD(std::vector<Vector2D>);

private:
	Vector3D calcIntersection(Vector3D, Vector3D, Vector3D, Vector3D);
	double calcAngle(Vector3D, Vector3D);

	int width, height;
	double lr, near, far;
	double iepsilon;

	Vector3D viewpoint;
	std::vector<Vector3D> axes3D; 
	Vector3D cyli_center; // center of top edge of cylinder 
};

#endif