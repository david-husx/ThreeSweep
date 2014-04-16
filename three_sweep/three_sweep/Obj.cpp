#include "Obj.h"

void Obj::display(){
	
}

void Obj::initScene(){
}

void Obj::insertSample(std::vector<Vector3D> v){
	assert(v.size() == sampleNum);
	if (topEdge.size() == 0){
		topEdge = v;
	}else{
		for (int i=0; i<sampleNum-1; i++){
			triangles.push_back(getTriangle(v[i], v[i+1], topEdge[i]));
			triangles.push_back(getTriangle(v[i+1], topEdge[i], topEdge[i+1]));
		}
		triangles.push_back(getTriangle(v[sampleNum-1], v[0], topEdge[sampleNum-1]));
		triangles.push_back(getTriangle(v[0], topEdge[0], topEdge[sampleNum-1]));
		topEdge = v;
	}
}

void Obj::getTriangle(Vector3D& v1, Vector3D& v2, Vector3D& v3){
	Triangle t;
	t[0] = v1;
	t[1] = v2;
	t[2] = v3;
	return t;
}