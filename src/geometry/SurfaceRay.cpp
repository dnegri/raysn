/*
 * SurfaceToSurfaceRay.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: jiyoon
 */

#include "SurfaceRay.h"



SurfaceRay::SurfaceRay() {
	// TODO Auto-generated constructor stub

}

SurfaceRay::~SurfaceRay() {
	// TODO Auto-generated destructor stub
}


void SurfaceRay::addSegment(Segment& segment) {
	segments.push_back(&segment);
}

