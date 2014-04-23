#include "InvCamera.h"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

InvCamera::InvCamera(int h, int w, double lr0, double n, double f)
{
	height = h;
	width = w;
	lr = lr0;
	near = n;
	far = f;
	iepsilon = 0.0001;
	viewpoint.x = viewpoint.y = viewpoint.z = 0;
}

/***********************************************************************
* This function is used to get coodinates of transformation from 2D 
* vertexs to 3D world coordinate
* @para x, y: four vertexs represents screen coordinate -- R, P1, P2, P3
* return value: four 3D world coordinate -- R, P1, P2, P3
* Author: Hu Sixing
* Date: Apr. 23th. 2014
************************************************************************/
std::vector<Vector3D> InvCamera::calcAxes(double* x, double* y)
{
	vector<Vector3D> direction;
	vector<Vector3D> input;
	for(int i=0;i<4;i++)
	{
		input.push_back(Vector3D(x[i]-height/2, y[i]-width/2, near));
		direction.push_back(input[i] - viewpoint);
		direction[i].normalize();
		
	}
	vector<Vector3D> axes3Dpoint;
	axes3Dpoint.push_back(input[0] + direction[0] * lr);

	double lx, ly;
	lx = 1;
	ly = 1000;
	Vector3D tempaxesX, a;
	double stride_lx = 1.0;
	while(abs(lx - ly) > stride_lx + stride_lx)
	{
		lx += stride_lx;
		tempaxesX = input[1] + direction[1] * lx;
		a = tempaxesX - axes3Dpoint[0];
		ly = (a * axes3Dpoint[0] - a * input[2]) / (a * direction[2]);
	}

	axes3Dpoint.push_back(input[1] + direction[1] * lx);
	axes3Dpoint.push_back(input[2] + direction[2] * ly);
	Vector3D zdir = cross(axes3Dpoint[1] - axes3Dpoint[0], axes3Dpoint[2] - axes3Dpoint[0]);
	zdir.normalize();
	//calculate the normal vector of plane(viewpoint, r, z)
	Vector3D plane_vzr_n = cross(input[3] - viewpoint, input[0] - viewpoint);
	plane_vzr_n.normalize();
	if(plane_vzr_n * zdir < iepsilon) // axes z is parallel to plane(viewpoint, r, z)
	{
		cout << "no precise solution!!!\n";
		//axes3D.clear();
		axes3Dpoint.push_back(axes3Dpoint[0] + zdir);////
	}
	else
	{
		axes3Dpoint.push_back(axes3Dpoint[0] + zdir);
	}

	// obtain the coordinates of 3D object
	axes3D.clear();
	cyli_center = (axes3Dpoint[1] + axes3Dpoint[2]) * 0.5;
	axes3D.push_back(axes3Dpoint[0]-cyli_center);
	axes3D.push_back(axes3Dpoint[3]-cyli_center);
	axes3D.push_back(zdir);
	for(int i=0;i<3;i++)
		axes3D[i].normalize();


	/////////////////////////////////////
	/*cerr << "\n----------------------\ndebug in InvCamera::calcAxes\n";
	cerr << "points:   ";
	for(int i=0;i<axes3Dpoint.size();i++)
	{
		axes3Dpoint[i].show();
	}
	cerr << "\nvector:  ";
	for(int i=1;i<axes3Dpoint.size();i++)
	{
		(axes3Dpoint[i]-axes3Dpoint[0]).show();
	}
	cerr << "\ncheck whether perpendicular or not\n";
	cerr << "x-y: " << (axes3Dpoint[1]-axes3Dpoint[0]) * (axes3Dpoint[2]-axes3Dpoint[0]) 
		 << "\nx-z: " << (axes3Dpoint[1]-axes3Dpoint[0]) * (axes3Dpoint[3]-axes3Dpoint[0]) 
		 << "\ny-z: " << (axes3Dpoint[2]-axes3Dpoint[0]) * (axes3Dpoint[3]-axes3Dpoint[0]);
	cerr << "\ncheck whether collinear or not\n";
	cerr << "v-r-R : "   << (axes3Dpoint[0]-input[0]).x / (input[0]-viewpoint).x << ' ' << (axes3Dpoint[0]-input[0]).y / (input[0]-viewpoint).y << ' ' << (axes3Dpoint[0]-input[0]).z / (input[0]-viewpoint).z
		 << "\nv-x-X : " << (axes3Dpoint[1]-input[1]).x / (input[1]-viewpoint).x << ' ' << (axes3Dpoint[1]-input[1]).y / (input[1]-viewpoint).y << ' ' << (axes3Dpoint[1]-input[1]).z / (input[1]-viewpoint).z
		 << "\nv-y-Y : " << (axes3Dpoint[2]-input[2]).x / (input[2]-viewpoint).x << ' ' << (axes3Dpoint[2]-input[2]).y / (input[2]-viewpoint).y << ' ' << (axes3Dpoint[2]-input[2]).z / (input[2]-viewpoint).z
		 << "\nv-z-Z : " << (axes3Dpoint[3]-input[3]).x / (input[3]-viewpoint).x << ' ' << (axes3Dpoint[3]-input[3]).y / (input[3]-viewpoint).y << ' ' << (axes3Dpoint[3]-input[3]).z / (input[3]-viewpoint).z;
	for(int i=0;i<4;i++)
	{
		(axes3Dpoint[i]-input[i]).show();
		cerr << "  ";
		(input[i]-viewpoint).show();
		cerr << endl;
	}
	cerr << "\n----------------------\n";*/
	/////////////////////////////////////

	return axes3Dpoint;
}

/***********************************************************************
* This function is used to transform 2D vertexs to 3D world coordinate
* @para v: two vertexs represents screen coordinate -- P1, P2
* return value: four 3D world coordinate -- P1, P2
* Author: Hu Sixing
* Date: Apr. 23th. 2014
************************************************************************/
std::vector<Vector3D> InvCamera::twoDtothreeD(std::vector<Vector2D> points)
{
	assert(points.size() >= 2);

	vector<Vector3D> input;
	input.push_back(Vector3D(points[0].x, points[0].y, near));
	input.push_back(Vector3D(points[1].x, points[1].y, near));
	
	Vector3D planeNormal = cross(input[0] - viewpoint, input[1] - viewpoint);
	planeNormal.normalize();
	Vector3D newCenter = calcIntersection(planeNormal, viewpoint, axes3D[2], cyli_center);
	double theta = calcAngle(input[0] - viewpoint, input[1] - viewpoint);
	double r = newCenter.distanceTo(viewpoint) * tan(theta/2);
	vector<Vector3D> res3Dpoint;
	res3Dpoint.push_back(newCenter - axes3D[1] * r);
	res3Dpoint.push_back(newCenter + axes3D[1] * r);

	return res3Dpoint;
}


/***********************************************************************
* private
* This function is used to calculate the intersection of a plane and a line
* @para planeNormal: the normal vector of the plane
* @para planePoint: one point of the plane
* @para lineDir: the direction vector of the line
* @para linePoint: one point of the line
* return value: the intersection
* Author: Hu Sixing
* Date: Apr. 23th. 2014
************************************************************************/
Vector3D InvCamera::calcIntersection(Vector3D planeNormal, Vector3D planePoint, Vector3D lineDir, Vector3D linePoint)
{
    Vector3D returnResult;
	double denominator = planeNormal * lineDir;
    if (denominator == 0)
    {
		cout << "InvCamera::getIntersection: no intersection\n";
    }
    else
    {
		double t = (planePoint - linePoint) * planeNormal / denominator;
		returnResult = linePoint + lineDir * t;
    }
    return returnResult;
}

/***********************************************************************
* private
* This function is used to calculate the included angle of two vectors
* @para v1, v2: two vectors
* return value: the included angle (PI)
* Author: Hu Sixing
* Date: Apr. 23th. 2014
************************************************************************/
double InvCamera::calcAngle(Vector3D v1, Vector3D v2)
{
	return acos((v1 * v2) / (v1.value() * v2.value()));
}