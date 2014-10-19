/*
 * RayInfo.cpp
 *
 *  Created on: Oct 15, 2014
 *      Author: jiyoon
 */

#include "RayInfo.h"



RayInfo::RayInfo() {
	RayInfo(0,0,0);
}

RayInfo::RayInfo(int nAziAngles, int nAziAnglesX2, double raySpace) :
	nAziAngles(nAziAngles), nAziAnglesX2(nAziAnglesX2), raySpace(raySpace) {

}

RayInfo::~RayInfo() {
}

int RayInfo::getAziAngles() const {
	return nAziAngles;
}

void RayInfo::setAziAngles(int aziAngles) {
	nAziAngles = aziAngles;
}

int RayInfo::getAziAnglesX2() const {
	return nAziAnglesX2;
}

void RayInfo::setAziAnglesX2(int aziAnglesX2) {
	nAziAnglesX2 = aziAnglesX2;
}

double RayInfo::getRaySpace() const {
	return raySpace;
}

void RayInfo::setRaySpace(double raySpace) {
	this->raySpace = raySpace;
}

