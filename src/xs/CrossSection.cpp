/*
 * CrossSection.cpp
 *
 *  Created on: Oct 17, 2014
 *      Author: jiyoon
 */

#include "CrossSection.h"


CrossSection::CrossSection(const int energyGroup) {

	this->energyGroup = energyGroup;

	nuFission  = new double[energyGroup]();
	total	   = new double[energyGroup]();
	transport  = new double[energyGroup]();
	chi		   = new double[energyGroup]();
	scattering = new double*[energyGroup]();

	for(int i=0; i<energyGroup; i++) {
		scattering[i] = new double[energyGroup]();
	}

}

CrossSection::~CrossSection() {

	delete [] total;
	delete [] transport;
	delete [] nuFission;
	delete [] chi;

	for(int i=0; i<energyGroup; i++) {
		delete [] scattering[i];
	}

	delete[] scattering;
}

void CrossSection::operator=(const CrossSection& crossSection) {
	for(int i=0; i<energyGroup; i++) {
		this->transport[i] = crossSection.transport[i];
		this->nuFission[i] = crossSection.nuFission[i];
		this->total[i]	   = crossSection.total[i];
		this->chi[i]	   = crossSection.chi[i];

		for(int j=0; j<energyGroup; j++) {
			this->scattering[i][j] = crossSection.scattering[i][j];
		}
	}
}
