#include "Boundary.h"
#include "EdgeExtraction.h"
#include <cassert>
#include <fstream>
#include <ctime>

using namespace std;

const double ZEROTHRESHOLD = 0.000001;

Boundary::Boundary()
{}

Boundary::Boundary(const string &imgName)
{
	init(imgName);
}

void Boundary::init(const string &imgName)
{
	edge.clear();

	Mat client_img = imread(imgName, CV_LOAD_IMAGE_GRAYSCALE);
	//imshow("ori", client_img);

	test_img = client_img;

	Mat edge_img = EdgeExtraction::extract(client_img);
	//imshow("edge", edge_img);
	//cv::waitKey(0);

	CmCurveEx::edge2vector(edge_img, true, this->edge);
	
}

/***********************************************************************
* This function is used to obtain exact intersection whose distance is the nearest to v
* @para v: two likely intersection given from interaction
* return value: two exact intersections whose sequence is same as v
* Author: Hu Sixing
* Date: Mar. 26th. 2014
************************************************************************/
vector<Vector2D> Boundary::calcIntersection(vector<Vector2D> v)
{
	assert(v.size() >= 2);
	
	int cir_amount = edge.size();// the amount of circles
	Vector2D p1(v[0]), p2(v[1]);
	Vector2D p3, p4;
	vector<Vector2D> candiate;//candiate intersections on line(v[0], v[1])
	//get all the intersections of each edge
	for(int i=0;i<cir_amount;i++)
	{
		int inter_id = 0;
		int length_edgei = edge[i].size();

		//cerr << i << " : " << length_edgei << endl;

		for(int j=0;j<length_edgei-1;j++)
		{
			p3 = edge[i][j];
			p4 = edge[i][j+1]; // MayToBeChange: compulsory circle or not  Now is not compulsory to be circle
			Vector2D intersection;
			if(getSegmentIntersection(Hline(p1, p2), Hline(p3, p4), intersection))
			{
				if(candiate.size() > 0 && 
					candiate[candiate.size()-1].x == intersection.x && candiate[candiate.size()-1].y == intersection.y)
				{
					continue;
				}
				else
				{
					candiate.push_back(intersection);
				}
			}
		}
	}

	/*cerr << "candiate: \n";
	for(unsigned int i=0; i<candiate.size(); i++)
	{
		cerr << "(" << candiate[i].x << ',' << candiate[i].y << ")   ";
	}
	cerr << endl;*/

	//cerr << "size = " << candiate.size() << endl;
	//select intersections and choose two intersections who is nearest to the v from interaction
	double x_min = min(p1.x, p2.x);
	double y_min = min(p1.y, p2.y);
	double x_max = max(p1.x, p2.x);
	double y_max = max(p1.y, p2.y);
	double delta_x = x_max - x_min;
	double p1_min1, p1_min2, p2_min1, p2_min2; //pi_minj means the lessat j distance(x direction) to pi
	int p1_min1_id, p1_min2_id, p2_min1_id, p2_min2_id;
	p1_min1 = p1_min2 = p2_min1 = p2_min2 = 10000000.0;
	p1_min1_id = p1_min2_id = p2_min1_id = p2_min2_id = -1;
	Vector2D temp_p;
	for(unsigned int i=0;i<candiate.size();i++)
	{
		temp_p = candiate[i];
		double distance2p1 = abs(temp_p.x - p1.x);
		double distance2p2 = abs(temp_p.x - p2.x);
		if(distance2p1 < distance2p2)
		{
			if(distance2p1 < p1_min1)
			{
				p1_min1 = distance2p1;
				p1_min1_id = i;
			}
			else if(distance2p1 < p1_min2)
			{
				p1_min2 = distance2p1;
				p1_min2_id = i;
			}
		}
		else
		{
			if(distance2p2 < p2_min1)
			{
				p2_min1 = distance2p2;
				p2_min1_id = i;
			}
			else if(distance2p2 < p2_min2)
			{
				p2_min2 = distance2p2;
				p2_min2_id = i;
			}
		}
	}

	vector<Vector2D> result;
	if(p1_min1_id == -1 && p2_min1_id == -1) //no intersection found
	{
		result.push_back(v[0]);
		result.push_back(v[1]);
	}
	else if(p1_min1_id == -1) //just one intersection is found which nearer p2
	{
		if(p2_min1*2 / delta_x > 0.2) // demand that the length of adjacent profiles does not vary more than 20% 
		{
			result.push_back(v[0]);
			result.push_back(v[1]);
		}
		else
		{
			Vector2D center;
			center = (v[0] + v[1]) * 0.5;
			Vector2D another_point;
			another_point = center * 2 - candiate[p2_min1_id];
			if(another_point.x > 0 && another_point.y > 0)
			{
				result.push_back(another_point);
				result.push_back(candiate[p2_min1_id]);
			}
		}
	}
	else if(p2_min1_id == -1) //just one intersection is found which nearer p1
	{
		if(p1_min1*2 / delta_x > 0.2) // demand that the length of adjacent profiles does not vary more than 20% 
		{
			result.push_back(v[0]);
			result.push_back(v[1]);
		}
		else
		{
			Vector2D center;
			center = (v[0] + v[1]) * 0.5;
			Vector2D another_point;
			another_point = center * 2 - candiate[p1_min1_id];
			if(another_point.x > 0 && another_point.y > 0)
			{
				result.push_back(another_point);
				result.push_back(candiate[p1_min1_id]);
			}
		}
	}
	else // two intersections are found
	{
		// demand that the length of adjacent profiles does not vary more than 20% 
		if(abs(candiate[p1_min1_id].x - candiate[p2_min1_id].x) / delta_x > 0.8)
		{
			result.push_back(candiate[p1_min1_id]);
			result.push_back(candiate[p2_min1_id]);
		}
		else if(p1_min2_id >= 0 && abs(candiate[p1_min2_id].x - candiate[p2_min1_id].x) / delta_x > 0.8)
		{
			result.push_back(candiate[p1_min2_id]);
			result.push_back(candiate[p2_min1_id]);
		}
		else if(p2_min2_id >= 0 && abs(candiate[p1_min1_id].x - candiate[p2_min2_id].x) / delta_x > 0.8)
		{
			result.push_back(candiate[p1_min1_id]);
			result.push_back(candiate[p2_min2_id]);
		}
		else if(p1_min2_id >= 0 && p2_min2_id >= 0 && abs(candiate[p1_min2_id].x - candiate[p2_min2_id].x) / delta_x > 0.8)
		{
			result.push_back(candiate[p1_min2_id]);
			result.push_back(candiate[p2_min2_id]);
		}
		else
		{
			result.push_back(v[0]);
			result.push_back(v[1]);
		}
	}

	/*cerr << "intersection result: ";
	result[0].show();
	result[1].show();
	cerr << endl;*/

	return result;
}

/************************************************************************
* private
* This function is used to obtain the point of intersection of segment line line1 and line line2
* @para line1: segment
* @para line2: line
* @para intersection: intersection of two segments [return]
* return value: whether the two segments intersect or not
* Author: Hu Sixing
* Date: Mar. 26th. 2014
************************************************************************/
bool Boundary::getSegmentIntersection(Hline line1, Hline line2, Vector2D &intersection)
{
	Vector2D p1(line1.first), p2(line1.second), p3(line2.first), p4(line2.second);
	//judge whether points of line2 are at different side of line1
	/*double d1, d2;
	Hvector p31(line2.first, line1.first), p32(line2.first, line1.second), p34(line2.first, line2.second);
	d1 = p31 * p34;//cross product
	d2 = p31 * p32;
	if(d1 * d2 > ZEROTHRESHOLD) //no intersection
		return false;
	else if(abs(d1) < ZEROTHRESHOLD)
	{
		double x_min = min(p3.x, p4.x);
		double y_min = min(p3.y, p4.y);
		double x_max = max(p3.x, p4.x);
		double y_max = max(p3.y, p4.y);
		if(p1.x >= x_min && p1.x <= x_max && p1.y >= y_min && p1.y <= y_max)   //line1.first is on segment line2
		{
			intersection.x = p1.x;
			intersection.y = p1.y;
			return true;
		}
		else
		{
			return false;
		}
	}
	else if(abs(d2) < ZEROTHRESHOLD)
	{
		double x_min = min(p3.x, p4.x);
		double y_min = min(p3.y, p4.y);
		double x_max = max(p3.x, p4.x);
		double y_max = max(p3.y, p4.y);
		if(p2.x >= x_min && p2.x <= x_max && p2.y >= y_min && p2.y <= y_max)   //line1.second is on segment line2
		{
			intersection.x = p2.x;
			intersection.y = p2.y;
			return true;
		}
		else
		{
			return false;
		}
	}*/

	//judge whether points of line1 are at different side of line2
	double d3, d4;
	Hvector p12(line1.first, line1.second), p13(line1.first, line2.first), p14(line1.first, line2.second);
	d3 = p12 * p13;//cross product
	d4 = p12 * p14;
	if(d3 * d4 > ZEROTHRESHOLD)
	{
		return false;
	}
	else if(abs(d3) < ZEROTHRESHOLD)
	{
		double x_min = min(p1.x, p2.x);
		double y_min = min(p1.y, p2.y);
		double x_max = max(p1.x, p2.x);
		double y_max = max(p1.y, p2.y);
		if(p3.x >= x_min && p3.x <= x_max && p3.y >= y_min && p3.y <= y_max)   //line2.first is on segment line1
		{
			intersection.x = p3.x;
			intersection.y = p3.y;
			return true;
		}
		else
		{
			return false;
		}
	}
	else if(abs(d4) < ZEROTHRESHOLD)
	{
		double x_min = min(p1.x, p2.x);
		double y_min = min(p1.y, p2.y);
		double x_max = max(p1.x, p2.x);
		double y_max = max(p1.y, p2.y);
		if(p4.x >= x_min && p4.x <= x_max && p4.y >= y_min && p4.y <= y_max)   //line2.second is on segment line1
		{
			intersection.x = p4.x;
			intersection.y = p4.y;
			return true;
		}
		else
		{
			return false;
		}
	}

	//indeed intersect   get intersection
    double denominator = (p2.y-p1.y) * (p4.x-p3.x) - (p1.x-p2.x) * (p3.y-p4.y);
    if(denominator == 0)
    {
        return false;
    }
    else
    {
        intersection.x =  ( (p2.x - p1.x) * (p4.x - p3.x) * (p3.y - p1.y) + 
			                (p2.y - p1.y) * (p4.x - p3.x) * p1.x - 
						    (p4.y - p3.y) * (p2.x - p1.x) * p3.x            ) / denominator;
        intersection.y = -( (p2.y - p1.y) * (p4.y - p3.y) * (p3.x - p1.x) + 
			                (p2.x - p1.x) * (p4.y - p3.y) * p1.y  - 
							(p4.x - p3.x) * (p2.y - p1.y) * p3.y            ) / denominator;
    }
	return true;
}


bool Boundary::setCycleGraph(std::vector<std::vector<Vector2D> > e)
{
	edge = e;
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////
void Boundary::test_getSegmentIntersection(string filename)
{
	clock_t start, next, finish;
	start = clock();

	//string filename("data/1221016.png");
	/*int cycle_amount;
	fin >> cycle_amount;
	vector<pair<int, vector<Vector2D> > > edge;
	for(int i=0;i<cycle_amount;i++)
	{
		pair<int, vector<Vector2D> > p;
		fin >> p.first;
		edge.push_back(p);
	}

	clock_t start, next, finish;
	start = clock();
	Vector2D v;
	vector<vector<Vector2D> > e;
	for(int i=0;i<cycle_amount;i++)
	{
		for(int j=0;j<edge[i].first;j++)
		{
			fin >> v.x;
			fin >> v.y;
			edge[i].second.push_back(v);
		}
		e.push_back(edge[i].second);
	}
	finish = clock();
	cerr << "read file finish...   time: " << double(finish-start)/1000.0 << "s\n\n";
	*/

	next = clock();
	init(filename);
	finish = clock();
	cerr << "\nBoundary::init finish...   time: " 
		 << double(finish-next)/1000.0 
		 << "s   total time: " << double(finish-start)/1000.0 << "s\n\n";

	cerr << "cycle amount = " <<edge.size() << endl;
	/*for(int i=0;i<edge.size();i++)
	{
		cerr << "vertex amount = " << edge[i].size() << endl;
		for(int j=0;j<edge[i].size()-1;j+=2)
		{
			cerr << "(" << edge[i][j] << ',' << edge[i][j+1] << ")  ";
		}
		cerr << endl;
	}
	cerr << "--------------------------" << endl;*/
	//system("pause");
	//setCycleGraph(e);

	vector<Vector2D> points;
	points.push_back(Vector2D(314, 233));
	points.push_back(Vector2D(340, 349));

	cerr << "interaction points: (314,233) (340,349)\n";
	next = clock();
	vector<Vector2D> res = calcIntersection(points);
	finish = clock();
	cerr << "\nBoundary::calcIntersection finish...   time: " 
		 << double(finish-next)/1000.0 
		 << "s   total time: " << double(finish-start)/1000.0 << "s\n";

	cerr << "-------------------------\n";
	cerr << "result: \n";
	for(unsigned int i=0;i<res.size();i++)
	{
		cerr << "(" << res[i].x << ',' << res[i].y << ")\n";
	}

	/*for(int i=0;i<2;i++)
	{
		test_img.ptr<uchar>(res[i].x)[res[i].y] = 255;
	}*/
}