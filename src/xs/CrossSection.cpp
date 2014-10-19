/*
 * CrossSection.cpp
 *
 *  Created on: Oct 17, 2014
 *      Author: jiyoon
 */

#include "CrossSection.h"


CrossSection::CrossSection(const int energyGroup) {

	this->energyGroup = energyGroup;

	nuFission = new double[energyGroup]();
	total = new double[energyGroup]();
	transport = new double[energyGroup]();
	chi = new double[energyGroup]();
	scattering = new double*[energyGroup]();

	for(int i=0;i<energyGroup;i++) {
		scattering[i] = new double[energyGroup]();
	}

}

CrossSection::~CrossSection() {

	delete [] total;
	delete [] transport;
	delete [] nuFission;
	delete [] chi;

	for(int i=0;i<energyGroup;i++) {
		delete [] scattering[i];
	}

	delete[] scattering;
}

