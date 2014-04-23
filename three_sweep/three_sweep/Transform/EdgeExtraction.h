#ifndef _EDGE_EXTRACTION_H_
#define _EDGE_EXTRACTION_H_

#include <opencv2\opencv.hpp>

class EdgeExtraction
{
public:
	EdgeExtraction();

	static cv::Mat extract(const cv::Mat&);
	static cv::Mat extract(const cv::Mat&, int, int, int);
};

#endif