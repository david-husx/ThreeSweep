#ifndef BASIC_H
#define BASIC_H

#include <math.h>

struct V3{
	double x;
	double y;
	double z;

	V3(){}
	V3(double x1, double x2, double x3): x(x1), y(x2), z(x3){}
	V3(const V3 &v): x(v.x), y(v.y), z(v.z){}

	V3 operator + (const V3 &v) { return V3(x+v.x, y+v.y, z+v.z); }
	V3 operator - (const V3 v)	{ return V3(x-v.x, y-v.y, z-v.z); }
	V3 operator * (const double t)	{ return V3(x*t, y*t, z*t); }
	V3 operator * (const double k[]) { return V3(x*k[0], y*k[1], z*k[2]); }
	double operator * (const V3 v)	{ return v.x*x+v.y*y + v.z*z;  }
	V3 operator / (const double t)	{ return V3(x/t, y/t, z/t); }

	double value(){ return sqrt(x*x+y*y+z*z);}
	double distanceTo(const V3 &p)	{ return sqrt(pow(x-p.x,2)+pow(y-p.y,2)+pow(z-p.z,2)); }
	void normalize(){ double v = value(); x /= v; y /= v; z /= v;  }
	void show() { printf("(%.2lf, %.2lf, %.2lf)", x, y, z);}
};

struct V2
{
	double x;
	double y;

	V2(){}
	V2(double _x, double _y): x(_x), y(_y){}
	V2(const V2& v): x(v.x), y(v.y){}

	V2 operator + (const V2 &v) { return V2(x+v.x, y+v.y); }
	V2 operator - (const V2 &v) { return V2(x-v.x, y-v.y); }
	V2 operator * (double t) { return V2(x*t, y*t); }
	void operator *= (double t) { x*= t; y*= t; }
	void operator /= (double t) { x/= t; y/= t; }

	double operator * (const V2 &v) { return x*v.x + y*v.y; }
	double value() {return sqrt(x*x+y*y); }
	double distanceTo(const V2 &p){ return sqrt(pow(x-p.x, 2)+pow(y-p.y, 2)); }

	void show(){printf("(%.2lf, %.2lf)", x, y);}
	V2 getNormal() { return V2(y, -x); }
};

typedef V3 Vector3D;
typedef V2 Vector2D;

typedef std::pair<Vector2D, Vector2D> Hline;

struct HVector
{
	double x, y;
	HVector(){}
	HVector(const Vector2D v1, const Vector2D v2) {x = v2.x-v1.x; y = v2.y-v1.y;} //vector(v1->v2)
	double operator * (const HVector &v) { return double(x*v.y - v.x*y); }//2D cross product
};
typedef HVector Hvector;
#endif;