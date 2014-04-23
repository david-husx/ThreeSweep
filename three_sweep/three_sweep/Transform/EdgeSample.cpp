#include "EdgeSample.h"

int EdgeSample::sampleNum = 24;

void EdgeSample::debugShow()
{
	cerr << "\nendpoint: ";
	endpoint[0].show();
	endpoint[1].show();
	cerr << "\nnormal: ";
	normal.show();
}