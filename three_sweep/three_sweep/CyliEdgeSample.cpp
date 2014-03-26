#include "CyliEdgeSample.h"

void CyliEdgeSample::init(std::vector<Vector2D> v){
	std::vector<Vector2D> cross = bounday->intersection(v);
	endPoint[0] = cross[0];
	endPoint[1] = cross[1];
	center = (endPoint[0] + endPoint[1])/2;
	a = endPoint[0].distanceTo(endPoint[1])/2;

	normal = cross[0] - cross[1];
	normal.normalize();
	normal = normal.getNormal();

	std::vector<Vector2D> v2;
	v2.push_back(v[1]);
	v2.push_back(v[2]);
	cross = bounday->intersection(v2);
	b = corss[1].distanceTo(center)/2;

	for (int i=0; i<24; i++){
		Vector2D p = getEllipsePoint(i);
		samples.push_back(p);
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


