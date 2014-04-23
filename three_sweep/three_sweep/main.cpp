#include <iostream>
#include <vector>
#include "Transform\boundary.h"
#include "CurveExtraction\CmCurveEx.h"
#include "Control.h"
#include "Transform\InvCamera.h"

using namespace std;

/*extern enum Instruct  {SETIMAGE, DRAW, DRAG, ROTATE};
extern enum Status {STRAIGHT, BEND};
extern enum BottomShape  { CIRCLE, SQUARE};*/

int main()
{
	Control control;
	control.setStatus(STRAIGHT);
	control.setBottomShape(CIRCLE);
	control.initBoundary("data/102943_curve.png");
	
	Vector2D x1(214, 472);
	Vector2D x2(360, 481);
	Vector2D x3(284, 503);
	/*Vector2D x1(525, 472);
	Vector2D x2(564, 392);
	Vector2D x3(554, 444);*/
	Vector2D d(1, 0);
	vector<Vector2D> first3points;
	first3points.push_back(Vector2D(214, 472));
	first3points.push_back(Vector2D(360, 481));
	first3points.push_back(Vector2D(284, 503));
	//214.0000   360.0000   284.0000   303.0000
	//472.0000   481.0000   503.0000   105.0000
	// 289  290  293
	// 451  428  396
	control.setFirstEdge(first3points);
	control.debugShow();

	control.getNewEdge(Vector2D(289, 451));
	control.debugShow();

	control.getNewEdge(Vector2D(290, 428));
	control.debugShow();

	control.getNewEdge(Vector2D(293, 396));
	control.debugShow();

	//Boundary b;
	//b.test_getSegmentIntersection("data/102943_curve.png");

	//string cImgFile = "data/102943_curve.png";
	//vector<vector<Vector2D> > edge;
	//CmCurveEx::edge2vector(cImgFile, true, edge);

	//InvCamera cam;
	/*vector<Vector2D> p2d;
	vector<Vector3D> p3d;
	
	Vector2D p;
	p.x = 64;
	p.y = 362;
	p2d.push_back(p);
	p.x = 61;
	p.y = 323;
	p2d.push_back(p);
	p.x = 90;
	p.y = 383;
	p2d.push_back(p);
	p.x = 133;
	p.y = 325;
	p2d.push_back(p);

	p3d = cam.twoD2threeD(p2d);
	cout << "-----------------------\n";
	for(int i=0;i<4;i++)
		cout << p3d[i].x << ' ' << p3d[i].y << ' ' << p3d[i].z << endl;
	cout << (p3d[1] - p3d[0]) * (p3d[2] - p3d[0]) << endl;*/

	system("pause");
	return 0;
}