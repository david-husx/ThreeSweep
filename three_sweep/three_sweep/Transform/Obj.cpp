#include "Obj.h"
#include <iostream>

void Obj::display(){
	
}

void Obj::initScene(){
}

void Obj::insertSample(std::vector<Vector3D> v){
	if (topEdge.size() == 0){
		topEdge = v;
	}else{
		Triangle t;
		for (int i=0; i<sampleNum-1; i++){
			setTriangle(t, v[i], v[i+1], topEdge[i]);
			triangles.push_back(t);

			setTriangle(t, v[i+1], topEdge[i], topEdge[i+1]);
			triangles.push_back(t);
		}
		setTriangle(t, v[sampleNum-1], v[0], topEdge[sampleNum-1]);
		triangles.push_back(t);
		setTriangle(t, v[0], topEdge[0], topEdge[sampleNum-1]);
		triangles.push_back(t);
		topEdge = v;
	}
}

void Obj::setTriangle(Triangle &t, Vector3D& v1, Vector3D& v2, Vector3D&v3){
	t.v[0] = v1;
	t.v[1] = v2;
	t.v[2] = v3;
}

void Obj::debugShow()
{
	std::cerr << "\ntopEdge: \n";
	for(int i=0;i<topEdge.size();i++)
	{
		std::cerr << "(" << topEdge[i].x << ',' << topEdge[i].y << ',' << topEdge[i].z << ")  ";
	}
	std::cerr << std::endl;
	std::cerr << "trangles: \n";
	for(int i=0;i<topEdge.size();i++)
	{
	}
	std::cerr << "\n--------------\n";
}