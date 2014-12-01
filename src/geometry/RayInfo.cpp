/*
 * RayInfo.cpp
 *
 *  Created on: Oct 15, 2014
 *      Author: jiyoon
 */

#include "RayInfo.h"



RayInfo::RayInfo() {
	RayInfo(0,0);
}

RayInfo::RayInfo(int nAziAngles, double raySpace) :
	nAziAngles(nAziAngles), raySpace(raySpace) {

}

RayInfo::~RayInfo() {
}

int RayInfo::getAziAngles() const {
	return nAziAngles;
}

void RayInfo::setAziAngles(int aziAngles) {
	nAziAngles = aziAngles;
}

double RayInfo::getRaySpace() const {
	return raySpace;
}

void RayInfo::setRaySpace(double raySpace) {
	this->raySpace = raySpace;
}

