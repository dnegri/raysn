/*
 * AzimuthalAngle.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jiyoon
 */

#include "AzimuthalAngle.h"



AzimuthalAngle::AzimuthalAngle() : surfacePoints() {
	angle	 = 0.0;
	vsine	 = 0.0;
	vcosine	 = 0.0;
	vtangent = 0.0;
	rayspace = 0.0;
	weight	 = 0.0;
}

AzimuthalAngle::~AzimuthalAngle() {
}

double AzimuthalAngle::getAngle() const {
	return angle;
}

void AzimuthalAngle::setAngle(double angle) {
	this->angle = angle;
	vsine		= sin(angle);
	vcosine		= cos(angle);
	vtangent	= tan(angle);
}

double AzimuthalAngle::getRayspace() const {
	return rayspace;
}

void AzimuthalAngle::setRayspace(double rayspace) {
	this->rayspace = rayspace;
}

boost::ptr_vector<SurfaceRayPoint>& AzimuthalAngle::getSurfacePoints() {
	return surfacePoints;
}

void AzimuthalAngle::addSurfaceRayPoint(SurfaceRayPoint& point) {
	surfacePoints.push_back(&point);
}

double AzimuthalAngle::getCosine()  const {
	return vcosine;
}

double AzimuthalAngle::getSine()  const {
	return vsine;
}

double AzimuthalAngle::getTangent()  const {
	return vtangent;
}

double AzimuthalAngle::getWeight()  const {
	return weight;
}

void AzimuthalAngle::setWeight(double weight) {
	this->weight = weight;
}

SurfaceRayPoint& AzimuthalAngle::findSurfaceRayPoints(const Point & point, const double width, const int surface) {

	int	   index = 0;

	double dx = width/nPointX;
	double dy = width/nPointY;

	switch(surface) {
	case NORTH:
		index = round(point.getX() / dx - 0.5);
		break;
	case SOUTH:
		index = nPointX + round(point.getX() / dx  - 0.5);
		break;
	case WEST:
		index = 2*nPointX + round(point.getY() / dy  - 0.5);
		break;
	case EAST:
		index = 2*nPointX + nPointY + round(point.getY() / dy  - 0.5);
		break;
	}

	return surfacePoints.at(index);
}



