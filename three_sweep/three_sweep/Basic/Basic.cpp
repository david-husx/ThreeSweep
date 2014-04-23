#include "Basic.h"

double getRotateAngle(double x1, double y1, double x2, double y2)
{
	const double epsilon = 1.0e-6;
	const double nyPI = acos(-1.0);
	double dist, dot, degree, angle;

	// normalize
	dist = sqrt( x1 * x1 + y1 * y1 );
	x1 /= dist;
	y1 /= dist;
	dist = sqrt( x2 * x2 + y2 * y2 );
	x2 /= dist;
	y2 /= dist;
	// dot product
	dot = x1 * x2 + y1 * y2;
	if ( fabs(dot-1.0) <= epsilon ) 
	angle = 0.0;
	else if ( fabs(dot+1.0) <= epsilon ) 
	angle = nyPI;
	else {
	double cross;

	angle = acos(dot);
	//cross product
	cross = x1 * y2 - x2 * y1;
	// vector p2 is clockwise from vector p1 
	// with respect to the origin (0.0)
	if (cross < 0 ) { 
	angle = 2 * nyPI - angle;
	}    
	}
	degree = angle *  180.0 / nyPI;
	return degree;
}

Vector3D cross(const Vector3D v1, const Vector3D v2)
{
	return Vector3D(v1.y*v2.z-v1.z*v2.y, v1.z*v2.x-v1.x*v2.z, v1.x*v2.y-v1.y*v2.x);
}