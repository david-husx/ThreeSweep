#ifndef COMPUTE3D_H
#define COMPUTE3D_H

#include "../Basic/Basic.h"
#include <vector>

class Compute3D{
	double zr;
    double t;
    double v;
    double n;
    double u;
public:
	void init(double N, double F);
	std::vector<Vector3D> calcAxes(double *, double *);

	static int sampleNum;
};

#endif