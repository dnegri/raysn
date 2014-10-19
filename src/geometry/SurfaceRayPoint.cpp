/*
 * SurfacePoint.cpp
 *
 *  Created on: Oct 15, 2014
 *      Author: jiyoon
 */

#include "SurfaceRayPoint.h"



SurfaceRayPoint::SurfaceRayPoint() {
	// TODO Auto-generated constructor stub

}

SurfaceRayPoint::~SurfaceRayPoint() {
	// TODO Auto-generated destructor stub
}

void SurfaceRayPoint::setCellSurface(Line& surface, int inews) {
	this->cellSurface = &surface;
	this->inews = inews;

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

void SurfaceRayPoint::setEndPoint(int islope, SurfaceRayPoint& point) {
	endPoints[islope] = &point;
}


