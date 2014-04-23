//#include "stdafx.h"
#include "Control.h"

void Control::setFirstEdge(std::vector<Vector2D> &v){
	switch(bottomShape){
		case CIRCLE:
			topEdge = new CyliEdgeSample;
			break;
		case SQUARE:
		default:
			break;
	}
	topEdge->setBoundary(boundary);
	topEdge->compute3D = translator;
	topEdge->init(v);
	topEdge->sample(0);
	obj->insertSample(topEdge->getSamples3D());
}

void Control::buildObj(Vector2D &mousePosition){
	getNewEdge(mousePosition);	
	obj->insertSample(topEdge->getSamples3D());
}

EdgeSample* Control::getNewEdge(Vector2D & mousePosition){
	EdgeSample* edgeSample = topEdge->clone();
	if (status == STRAIGHT){
		Vector2D direct = edgeSample->getNormal()*
						 (edgeSample->getNormal()*(mousePosition - oldMousePosition));
	
		edgeSample->endpoint[0] += direct;
		edgeSample->endpoint[1] += direct;
		edgeSample->center += direct;
		edgeSample->setEndpoint(edgeSample->boundary->calcIntersection(edgeSample->getEndpoint()));

		edgeSample->clear();
		
		edgeSample->sample(1);

	}else if(status == BEND) {
		// the way we get normal should be discussed again
		Vector2D n = mousePosition - oldMousePosition;
		n.normalize();
		edgeSample->setNormal(n);

		double angle = getRotateAngle(n.x, n.y, 
					   topEdge->getNormal().x, topEdge->getNormal().y);
		// direct means the direct from center to endpoint
		Vector2D oldDirect = topEdge->getEndpoint()[0] - topEdge->getCenter();
		double x = oldDirect.x* cos(angle) - oldDirect.y* sin(angle);
		double y = oldDirect.x* sin(angle) + oldDirect.y* cos(angle);
		Vector2D newDirect(x, y);

		// set new center and endpoint 
		edgeSample->setCenter(edgeSample->getCenter() + n);
		std::vector<Vector2D> endpoint;
		endpoint.push_back(edgeSample->getCenter() - newDirect);
		endpoint.push_back(edgeSample->getCenter() + newDirect);
		edgeSample->setEndpoint(edgeSample->boundary->calcIntersection(endpoint));

		// set sample points 
		edgeSample->sample(1); 
	}
	else{
		std::cout << "status is wrong" << endl;
		return NULL;
	}

	delete topEdge;
	topEdge = edgeSample;
	oldMousePosition = mousePosition;
	return topEdge;
}

void Control::debugShow()
{
	topEdge->debugShow();
	obj->debugShow();
}