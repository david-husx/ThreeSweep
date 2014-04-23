#ifndef  CONTROL_H
#define	 CONTROL_H

#include "Basic\Basic.h"
#include "Transform\Boundary.h"
#include "Transform\Compute3D.h"
#include "Transform\CyliEdgeSample.h"
#include "Transform\Obj.h"

enum Instruct  {SETIMAGE, DRAW, DRAG, ROTATE};
enum Status {STRAIGHT, BEND};
enum BottomShape  { CIRCLE, SQUARE};

class Control{
public:
	Control(){
		obj = new Obj;
		topEdge = NULL;
		translator = new Compute3D;		
		translator->init(10, 800);
	}
	~Control(){
		delete translator;
		delete obj;
		delete topEdge;
		delete boundary;
	}

	void control(char* buffer){
	}

	EdgeSample* getNewEdge(Vector2D &mousePosition);

	void setImage(char* filename) {}
	void buildObj(Vector2D &mousePosition);
	void initBoundary(char* filename){
		boundary = new Boundary;
		boundary->init(string(filename));
	}

	void setInstruct(Instruct i) { instruct = i; }
	void setStatus(Status s) { status = s; }
	void setFirstEdge(std::vector<Vector2D> &v);
	void setBottomShape(BottomShape b) { bottomShape = b; }

	Obj* getObj() { return obj; }

	void debugShow();

	
private:
	Status status;
	Instruct instruct;
	BottomShape bottomShape;
	Obj* obj;
	EdgeSample* topEdge;
	Compute3D* translator;
	Vector2D oldMousePosition;
	Boundary* boundary;
};

#endif