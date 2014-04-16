#ifndef _INVCAMERA_H_
#define _INVCAMERA_H_

//#include "Basic.h"
#include "library.h"

/***********************************************************************
* This class is used to calculate 3D coordinates from 2D coordinates (of picture)
* Author: Hu Sixing
* Date  : Apr. 16th. 2014
************************************************************************/
class InvCamera
{
public:
	InvCamera();
	std::vector<Vector3D> twoD2threeD(std::vector<Vector2D>);

private:
	void calPara(int, int, int);

	double n, u, v;
	double zr;
};

#endif