#ifndef CONTROL_H
#define	CONTROL_H

#include "EdgeSample.h"
#include "CyliEdgeSample.h"

enum Instruct = {draw, drag, rotate};

class Control{
public:
	void control(Instruct is){
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
	}

	EdgeSample getNewEdge(){
		return NULL;
	}
	
	
}；

#endif