#ifndef _CMCURVEEX_H_
#define _CMCURVEEX_H_

#pragma once

/***********************************************************************/
/*  This software is developed by Ming-Ming Cheng.				       */
/*       Url: http://cg.cs.tsinghua.edu.cn/people/~cmm/                */
/*  This software is free fro non-commercial use. In order to use this */
/*  software for academic use, you must cite the corresponding paper:  */
/*      Ming-Ming Cheng, Curve Structure Extraction for Cartoon Images,*/
/*		Proceedings of NCMT 2009, 1-8								   */	
/***********************************************************************/
/***********************************************************************
* This class is used to extract every vertex from edge a graph
* Author : Cheng Ming-ming
* Comment: Hu Sixing
* Date   : Apr. 1st. 2014
************************************************************************/

#include "CurveExtractionStdafx.h"
#include "../Basic/Basic.h"

class CmCurveEx
{
public:
	typedef struct CEdge
	{
		CEdge(int _index) {index = _index; }
		~CEdge(void){}

		// Domains assigned during link();
		int index;    // Start from 0
		int pointNum; 
		Point start, end; 
		vector<Point> pnts; 
	} CEdge;

	CmCurveEx(const Mat& srcImg1f, float maxOrntDif = 0.25f * CV_PI);
	
	// Input kernel size for calculating derivatives, kSize should be 1, 3, 5 or 7
	const Mat& CalSecDer(int kSize = 5, float linkEndBound = 0.01f, float linkStartBound = 0.1f);
	const Mat& CalFirDer(int kSize = 5, float linkEndBound = 0.01f, float linkStartBound = 0.1f);
	const vector<CEdge>& Link(int shortRemoveBound = 3);

	// Get data pointers
	const Mat& GetDer(){ return m_pDer1f; }
	const Mat& GetLineIdx() { return m_pLabel1i; } // Edge index start from 1
	const Mat& GetNextMap() { return m_pNext1i; }
	const Mat& GetOrnt() { return m_pOrnt1f; }
	const vector<CEdge>& GetEdges() {return m_vEdge;}

	static const int IND_BG = 0xffffffff, IND_NMS = 0xfffffffe, IND_SR = 0xfffffffd; // Background, Non Maximal Suppress and Short Remove

	static void edge2vector(const Mat &img1u, bool isCartoon, std::vector<std::vector<Vector2D> > &edge); 
	//if (isCartoon) the width of edges is 1; else not 

private:
	const Mat &m_img1f; // Input image

	Mat m_pDer1f;   // First or secondary derivatives. 32FC1
	Mat m_pOrnt1f;  // Line orientation. 32FC1
	Mat m_pLabel1i;  // Line index, 32SC1.
	Mat m_pNext1i;   // Next point 8-direction index, [0, 1, ...,  7], 32SC1

	// Will be used for link process
	typedef pair<float, Point> PntImp;
	vector<PntImp> m_StartPnt;
	vector<CEdge> m_vEdge;
	static bool linePointGreater (const PntImp& e1, const PntImp& e2 ) {return e1.first > e2.first;};

	int m_h, m_w; // Image size	
	int m_kSize; // Smooth kernel size: 1, 3, 5, 7
	float m_maxAngDif; // maximal allowed angle difference in a curve

	void NoneMaximalSuppress(float linkEndBound, float linkStartBound);
	void findEdge(Point seed, CEdge& crtEdge, bool isBackWard);
	bool goNext(Point &pnt, float& ornt, CEdge& crtEdge, int orntInd, bool isBackward);
	bool jumpNext(Point &pnt, float& ornt, CEdge& crtEdge, int orntInd, bool isBackward);

	/* Compute the eigenvalues and eigenvectors of the Hessian matrix given by
	dfdrr, dfdrc, and dfdcc, and sort them in descending order according to
	their absolute values. */
	static void compute_eigenvals(double dfdrr, double dfdrc, double dfdcc, double eigval[2], double eigvec[2][2]);
	
	static inline float angle(float ornt1, float orn2);
	static inline void refreshOrnt(float& ornt, float& newOrnt);
};

typedef CmCurveEx::CEdge CmEdge;
typedef vector<CmEdge> CmEdges;

#endif