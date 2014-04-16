#include "InvCamera.h"

using namespace std;

InvCamera::InvCamera()
{
	calPara(5, 20, 8);
}

/***********************************************************************
* This function is used to transform 2D vertexs to 3D world coordinate
* @para v: four vertexs represents screen coordinate -- R, P1, P2, P3
* return value: fout 3D world coordinate -- R, P1, P2, P3
* Author: Hu Sixing
* Date: Apr. 16th. 2014
************************************************************************/
vector<Vector3D> InvCamera::twoD2threeD(vector<Vector2D> points)
{
	double C[4][4];
	double c = v / n;
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			C[i][j] = points[i].x * points[j].x + points[i].y * points[j].y + c * c;
		}
	double zm[4]; //depth value + v
	zm[0] = zr + v;
	int rr, mm, nn, ll;
	for(int i=1;i<4;i++)
	{
		rr = 0;
		mm = i;
		nn = i % 3 + 1;
		ll = (i+1) % 3 + 1;
		zm[i] = (C[rr][mm]*C[rr][mm]*C[nn][ll] - C[rr][ll]*C[rr][mm]*C[nn][mm] - C[rr][nn]*C[rr][mm]*C[ll][mm] + C[rr][rr]*C[ll][mm]*C[nn][mm]) / 
		        (C[rr][rr]*C[rr][rr]*C[ll][nn] - C[rr][rr]*C[rr][ll]*C[rr][nn]) * zm[0];
	}

	//choose +-zm
	for(int i=1;i<4;i++)
		if(zm[i] < 0)
			zm[i] = zm[i] * (-1);
	for(int i=0;i<4;i++)
	{
		cerr << "zm[" << i << "] = " << zm[i] << endl;
	}
	//

	vector<Vector3D> wc; //world coordinate
	for(int i=0;i<4;i++)
	{
		Vector3D tempp;
		tempp.x = n * points[i].x / zm[i];
		tempp.y = n * points[i].y / zm[i];
		tempp.z = u / zm[i];
		wc.push_back(tempp);
	}
	return wc;
}


/***********************************************************************
* private
* This function is used to calculate parameters u, v, n
* @para near: the depth of near boundary plain
* @para far : the depth of far boundry plain
* @para zr0 : the depth of origin point R
* Author: Hu Sixing
* Date: Apr. 16th. 2014
************************************************************************/
void InvCamera::calPara(int near, int far, int zr0)
{
	n = -far;
	v = (-1) * (far + near);
	u = far * near;
	zr = zr0;
}