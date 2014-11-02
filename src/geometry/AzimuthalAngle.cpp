/*
 * AzimuthalAngle.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jiyoon
 */

#include "AzimuthalAngle.h"



AzimuthalAngle::AzimuthalAngle(int index) : index(index) {
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


