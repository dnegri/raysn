/*
 * CellSurfaceType.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: jiyoon
 */

#include "CellTypeSurface.h"

CellTypeSurface::CellTypeSurface() {}

CellTypeSurface::CellTypeSurface(int nAngles, int inews, double length) {
	// TODO Auto-generated constructor stub

	for(int i=0; i<nAngles; i++) {
		surfacePoints.push_back(new boost::ptr_vector<SurfaceRayPoint>());
	}
	
	this->inews = inews;
	this->length = length;
	
	switch(inews) {
	case NORTH:
		dir[POSITIVE].x = PLUS;
		dir[POSITIVE].y = PLUS;

		dir[NEGATIVE].x = MINUS;
		dir[NEGATIVE].y = PLUS;

		break;
	case SOUTH:
		dir[POSITIVE].x = MINUS;
		dir[POSITIVE].y = MINUS;

		dir[NEGATIVE].x = PLUS;
		dir[NEGATIVE].y = MINUS;

		break;
	case WEST:
		dir[POSITIVE].x = PLUS;
		dir[POSITIVE].y = PLUS;

		dir[NEGATIVE].x = PLUS;
		dir[NEGATIVE].y = MINUS;

		break;
	case EAST:
		dir[POSITIVE].x = MINUS;
		dir[POSITIVE].y = MINUS;

		dir[NEGATIVE].x = MINUS;
		dir[NEGATIVE].y = PLUS;
		break;
	}
	
}

CellTypeSurface::~CellTypeSurface() {
	// TODO Auto-generated destructor stub
}


boost::ptr_vector<SurfaceRayPoint>& CellTypeSurface::getPoints(AzimuthalAngle& angle) {
	return surfacePoints.at(angle.getIndex());
}

void CellTypeSurface::addPoint(AzimuthalAngle& angle, SurfaceRayPoint& point) {
	point.setIndex((int) surfacePoints.at(angle.getIndex()).size());
	surfacePoints.at(angle.getIndex()).push_back(&point);
}

SurfaceRayPoint& CellTypeSurface::findPoint(AzimuthalAngle& angle, double point) {

	int nPoints = (int) surfacePoints.at(angle.getIndex()).size();
	double delta = length / nPoints;
	
	int index = round(point / delta - 0.5);

	return surfacePoints.at(angle.getIndex()).at(index);
}

