/*
 * Line.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jiyoon
 */

#include "Line.h"



Line::Line() {
	subRegions[0] = NULL;
	subRegions[1] = NULL;

}

Line::~Line() {

}

void Line::setBeginPoint(Point& beginPoint) {
	this->beginPoint = &beginPoint;
}

void Line::setEndPoint(Point& endPoint) {
	this->endPoint = &endPoint;
}

SubRegionType& Line::getNeighborSubRegion(SubRegionType& subRegion) {
	if (subRegions[0] == &subRegion) {
		return *subRegions[1];
	}
	else {
		return *subRegions[0];
	}
}

bool Line::cross(const Point& point, double& slope, int& dirX, int& dirY,
				 Point& cross, double& length) const {

	Point  dxy = (*endPoint) - (*beginPoint);

	double yint = point.getY() - slope * point.getX();

	if (fabs(dxy.getX()) < MICRO) {
		cross.setX(beginPoint->getX());
		cross.setY(slope * cross.getX() + yint);
	}
	else if (fabs(dxy.getY()) < MICRO) {
		cross.setY(beginPoint->getY());
		cross.setX((cross.getY() - yint) / slope);
	}
	else {
		double aa2 = dxy.getY() / dxy.getX();
		double bb2 = beginPoint->getY() - aa2 * beginPoint->getX();
		cross.setX((yint - bb2) / (aa2 - slope));
		cross.setY(slope * cross.getX() + yint);
	}

	bool crossed = (endPoint->getX() - cross.getX())
				   * (beginPoint->getX() - cross.getX()) < MICRO;
	crossed = crossed
			  && (endPoint->getY() - cross.getY())
			  * (beginPoint->getY() - cross.getY()) < MICRO;

	if (crossed) {
		dxy		= cross - point;
		crossed = copysign(dxy.getX(), (double) dirX) == dxy.getX()
				  && copysign(dxy.getY(), (double) dirY) == dxy.getY();
	}

	length = 0.0;
	if (crossed) {
		length = dxy.norm();
	}

	return crossed;
}

void Line::addSubRegion(SubRegionType& subRegion) {
	if (subRegions[0] == NULL) {
		subRegions[0] = &subRegion;
	}
	else if (subRegions[1] == NULL) {
		subRegions[1] = &subRegion;
	}
	else {
		log4cpp::Category::getRoot().error("Too many SubRegions for a line");
		throw std::runtime_error("too many subRegions for a line");
	}
}


