/*
 * SubRegion.cpp
 *
 *  Created on: Oct 17, 2014
 *      Author: jiyoon
 */

#include "SubRegion.h"

SubRegion::SubRegion(int energyGroup, SubRegionType& type) : type(&type) {

	flux   = new double[energyGroup];
	source = new double[energyGroup];

	for(int ig=0; ig < energyGroup; ig++) {
		flux[ig] = 1.0;
	}
}

SubRegion::~SubRegion() {
	delete [] flux;
	delete [] source;
}


double SubRegion::calculateFissionSource(const CrossSection& xs) {

	fissionSource = 0;
	for(int ig=0; ig < xs.getEnergyGroup(); ig++) {
		fissionSource += (xs.getNuFission()[ig]*flux[ig]);
	}

	return fissionSource;
}

void SubRegion::calculateSource(const CrossSection& xs, int group, double reigv) {
	source[group] = reigv*xs.getChi()[group]*fissionSource;

	for(int ig=0; ig < xs.getEnergyGroup(); ig++) {
		source[group] += (xs.getScattering()[group][ig]*flux[ig]);
	}
	source[group] -= (xs.getScattering()[group][group]*flux[group]);

	source[group]  = source[group]/xs.getTransport()[group];

}

void SubRegion::addSelfScattering(const CrossSection& xs, int group) {
	source[group] += (xs.getScattering()[group][group]*flux[group])/xs.getTransport()[group];
}

void SubRegion::addOneGroupFlux(int group, double flux) {
	this->flux[group] += flux;
}

void SubRegion::clearOneGroupFlux(int group) {
	this->flux[group] = 0.0;
}

void SubRegion::makeOneGroupFlux(const CrossSection& xs, int group) {
	flux[group] = flux[group] / (xs.getTransport()[group] * type->getVolume()) + source[group];
}
