#include "CyliEdgeSample.h"

void CyliEdgeSample::init(std::vector<Vector2D> v){
	endpoint = bounday->intersection(v);
	center = (endpoint[0] + endpoint[1])/2;
	a = endpoint[0].distanceTo(endpoint[1])/2;

	normal = endpoint[1] - endpoint[0];
	normal.normalize();
	normal = normal.getNormal();

	std::vector<Vector2D> v2;
	v2.push_back(v[1]);
	v2.push_back(v[2]);
	v2 = bounday->intersection(v2);
	b = v2[1].distanceTo(center)/2;

	if (normal*(v2[1] - v2[0]) > 0){
		normal *= -1;
	}
	sample();
}

void CyliEdgeSample::sample(){
	double t = b/a;
	a = endpoint[0].distanceTo(endpoint[1])/2;
	b = t*a;

	for (int i=0; i<sampleNum; i++){
		Vector2D p = getEllipsePoint(i);
		// someting may be done to make it faster here
		angle = atan(normal.x/normal.y);
		Vector2D sample(p.x*cos(angle)-p.y*sin(angle), 
						p.x*sin(angle)+p.y*cos(angle));
		samples.push_back(sample+center);
	}
}

Vector2D CyliEdgeSample::getEllipsePoint(int i){
	Vector2D v;
	v.x = 4*a*i/sampleNum;
	if (i < sampleNum/4 || i>3*sampleNum/4){
		v.x = -1*v.x;
	}
	v.y = b*sqrt(1-v.x*v.x/(a*a));
	if (i < sampleNum/2){
		v.y = -1*v.y;
	}

	return v;
}


CyliEdgeSample CyliEdgeSample::clone(){
	CyliEdgeSample ces;
	ces.setCenter(center);
	ces.setNormal(normal);
	ces.setA(a);
	ces.setB(b);
	ces.setEndpoint(endpoint);

	return ces;
}