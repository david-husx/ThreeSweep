#ifndef CONTROL_H
#define	CONTROL_H

#include "EdgeSample.h"
#include "CyliEdgeSample.h"
#include "library.h"

class Control{
public:
	Control(){
		obj = new Obj;
		topEdge = NULL;
		compute3D = new Compute3D;		
	}
	~Control(){
		delete compute3D;
		delete obj;
		delete topEdge;
	}
	/*void control(Instruct is){
		switch is{
			case draw:
				break;
			case drag:
				break;
			case rotate:
				break;
			default:
				break;
		}
	}*/

	EdgeSample getNewEdge(Vector2D &mousePosition);
	void initBoundary(){
		boundary = new Boundary;
		boundary->init();
	}
	void setStatus(Status &s) { status = s; }
	void setFirstEdge(std::vector<Vector2D> &v);
	void setBottomShape(BottomShape b) { bottomShape = b; }

	Obj* getObj() { return &obj; }
	void objAddSample() { obj.insertSample(compute3D->compute3D(topEdge->getSample())); }
private:
	Status status;
	BottomShape bottomShape;
	Obj* obj;
	Vector2D oldMoustPosition;
	EdgeSample* topEdge;
	Compute3D* compute3D;
	Boundary* boundary;

	enum Instruct = {draw, drag, rotate};
	enum Status = {straight, bend};
	enum BottomShape = { circle, square};
}；

#endif