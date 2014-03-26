#include "library.h"
#include "Boundary.h"
#include <cassert>
#include <fstream>
using namespace std;

const double ZEROTHRESHOLD = 0.000001;

void Boundary::init()
{

}

/***************************************
* This function is used to obtain exact intersection whose distance is the nearest to v
* @para v: two likely intersection given from interaction
* return value: two exact intersections whose sequence is same as v
***************************************/
vector<Vector2D> Boundary::calcIntersection(vector<Vector2D> v)
{
	assert(v.size() == 2);

	int cir_amount = edge.size();// the amount of circles
	Vector2D p1(v[0]), p2(v[1]);
	Vector2D p3, p4;
	vector<vector<Vector2D> > candiate;//each circle takes up a dimension and each dimension has one or two intersections
	int cand_id = -1;
	//get all the intersections of each circle
	for(int i=0;i<cir_amount;i++)
	{
		int inter_id = 0;
		int length_edgei = edge[i].size();
		for(int j=0;j<length_edgei;j++)
		{
			p3 = edge[i][j];
			p4 = edge[i][(j+1)%length_edgei]; // MayToBeChange: compulsory circle or not
			Vector2D intersection;
			if(getSegmentIntersection(Hline(p1, p2), Hline(p3, p4), intersection))
			{
				cerr << i << ' '<< j << ' ' << cand_id << ' ' << inter_id << "  : (" << intersection.x << ',' << intersection.y << ")" << endl;
				if(inter_id >= 2) //do not accept more than 2 intersections on one circle
				{
					if(abs(candiate[cand_id][inter_id-1].x - intersection.x) > ZEROTHRESHOLD || 
					   abs(candiate[cand_id][inter_id-1].y - intersection.y) > ZEROTHRESHOLD   ) // ignore duplicated intersection
					{
						candiate.pop_back();
						cand_id--;
						inter_id = 0;
						break;
					}
				}
				else if(inter_id == 1)
				{
					if(abs(candiate[cand_id][inter_id-1].x - intersection.x) > ZEROTHRESHOLD || 
					   abs(candiate[cand_id][inter_id-1].y - intersection.y) > ZEROTHRESHOLD   )// ignore duplicated intersection
					{
						candiate[cand_id].push_back(intersection);
						inter_id++;
					}
				}
				else
				{
					vector<Vector2D> newCand;
					newCand.push_back(intersection);
					candiate.push_back(newCand);
					cand_id++;
					inter_id++;
				}
				//system("pause");
			}
		}
	}

	cerr << "candiate: \n";
	for(int i=0;i<candiate.size();i++)
	{
		for(int j=0;j<candiate[i].size();j++)
		{
			cerr << "(" << candiate[i][j].x << ',' << candiate[i][j].y << ")   ";
		}
		cerr << endl;
	}

	//select intersections and choose two intersections who is nearest to the v from interaction
	double x_min = min(p1.x, p2.x);
	double y_min = min(p1.y, p2.y);
	double x_max = max(p1.x, p2.x);
	double y_max = max(p1.y, p2.y);
	double delta_x = x_max - x_min;
	double delta_x1_min = 100000000.0, delta_x2_min = 100000000.0, delta_x_min = 100000000.0;
	int p1_id_min = -1; //p1_id_min: the intersection which is attach to p1.  used when length_candi == 2
	int p_id_min = -1;//p_id_min: pi which is nearer the intersection.  used when length_candi == 1 
	int choose1_id = -1, choose2_id = -1;//choosei_id: i = length_candi -- which item is the result candiate
	for(int i=0;i<candiate.size();i++)
	{
		int length_candi = candiate[i].size();
		if(length_candi == 1)
		{
			Vector2D pp(candiate[i][0]);
			//choose the nearest and the length does not vary more than 20%
			if(abs(pp.x-p1.x) < delta_x_min && abs(pp.x-p1.x)/delta_x < 0.2)
			{
				delta_x_min = abs(pp.x-p1.x);
				p_id_min = 1;
				choose1_id = i;
			}
			else if(abs(pp.x-p2.x) < delta_x_min && abs(pp.x-p2.x)/delta_x < 0.2)
			{
				delta_x_min = abs(pp.x-p2.x);
				p_id_min = 2;
				choose1_id = i;
			}
		}
		else if(length_candi == 2)
		{
			Vector2D pp1(candiate[i][0]), pp2(candiate[i][1]);
			double temp_min1, temp_min2;
			double temp_p1_id_min, temp_p2_id_min;
			if(abs(p1.x-pp1.x) < abs(p1.x-pp2.x))
			{
				temp_min1 = abs(p1.x-pp1.x);
				temp_min2 = abs(p2.x-pp2.x);
				temp_p1_id_min = 1;
			}
			else
			{
				temp_min1 = abs(p1.x-pp2.x);
				temp_min2 = abs(p2.x-pp1.x);
				temp_p1_id_min = 2;
			}
			//choose the nearest and the length does not vary more than 20%
			if(temp_min1 + temp_min2 < delta_x2_min && abs(pp1.x-pp2.x)/delta_x > 0.8)
			{
				delta_x2_min = temp_min1 + temp_min2;
				choose2_id = i;
				p1_id_min = temp_p1_id_min;
			}
		}
	}

	vector<Vector2D> result;
	if(choose2_id != -1)
	{
		if(p1_id_min == 1)
		{
			result.push_back(candiate[choose2_id][0]);
			result.push_back(candiate[choose2_id][1]);
		}
		else
		{
			result.push_back(candiate[choose2_id][1]);
			result.push_back(candiate[choose2_id][0]);
		}
	}
	else if(choose1_id != -1)
	{
		Vector2D center((v[0].x+v[1].x)/2, (v[0].y+v[1].y)/2);
		Vector2D another_intersection;
		another_intersection.x = 2 * center.x - candiate[choose1_id][0].x;
		another_intersection.y = 2 * center.y - candiate[choose1_id][0].y;
		if(p_id_min == 1)
		{
			result.push_back(candiate[choose1_id][0]);
			result.push_back(another_intersection);
		}
		else
		{
			result.push_back(another_intersection);
			result.push_back(candiate[choose1_id][0]);
		}
	}
	else
	{
		result.push_back(v[0]);
		result.push_back(v[1]);
	}

	return result;
}

/***************************************
* private
* This function is used to obtain the point of intersection of segment line line1 and line line2
* @para line1: segment
* @para line2: line
* @para intersection: intersection of two segments [return]
* return value: whether the two segments intersect or not
***************************************/
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
void Boundary::test_getSegmentIntersection()
{
	ifstream fin("zcycle.txt");
	int cycle_amount;
	fin >> cycle_amount;
	vector<pair<int, vector<Vector2D> > > edge;
	for(int i=0;i<cycle_amount;i++)
	{
		pair<int, vector<Vector2D> > p;
		fin >> p.first;
		edge.push_back(p);
	}

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
	cerr << "read file finish...\n";

	
	cerr << "cycle amount = " << cycle_amount << endl;
	for(int i=0;i<cycle_amount;i++)
	{
		cerr << "vertex amount = " << edge[i].first << endl;
		for(int j=0;j<edge[i].first;j++)
		{
			cerr << "(" << e[i][j].x << ',' << e[i][j].y << ")  ";
		}
		cerr << endl;
	}
	cerr << "--------------------------" << endl;

	setCycleGraph(e);

	vector<Vector2D> points;
	points.push_back(Vector2D(0.9,4.1));
	points.push_back(Vector2D(3.3,1.7));

	vector<Vector2D> res = calcIntersection(points);

	cerr << "-------------------------\n";
	cerr << "result: \n";
	for(int i=0;i<res.size();i++)
	{
		cerr << "(" << res[i].x << ',' << res[i].y << ")\n";
	}

}