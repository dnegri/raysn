/*
 * XSLibrary.cpp
 *
 *  Created on: Oct 17, 2014
 *      Author: jiyoon
 */

#include "XSLibrary.h"


XSLibrary::XSLibrary() {
	// TODO Auto-generated constructor stub

}

XSLibrary::~XSLibrary() {
	// TODO Auto-generated destructor stub
}

void XSLibrary::initialize() {

	energyGroup = 2;

	CrossSection* xs = new CrossSection(energyGroup);

	xs->getTransport()[0] = 2.706530E-02;
	xs->getTransport()[1] = 7.233540e-02;
	
	xs->getNuFission()[0] = 5.576590e-03;
	xs->getNuFission()[1] = 9.986290e-02;

	xs->getChi()[0]	= 1.000000E+00;
	xs->getChi()[1]	= 0.000000E+00;
	
	xs->getScattering()[0][0] = 0.000000E+00;
	xs->getScattering()[0][1] = 0.000000E+00;
	xs->getScattering()[1][0] = 1.800400e-02;
	xs->getScattering()[1][1] = 0.000000E+00;

	crossSections.push_back(xs);

	xs = new CrossSection(energyGroup);
	
	xs->getTransport()[0] = 2.682870E-02;
	xs->getTransport()[1] = 1.772150e-02;
	
	xs->getNuFission()[0] = 0.000000E+00;
	xs->getNuFission()[1] = 0.000000E+00;

	xs->getChi()[0]	= 1.000000E+00;
	xs->getChi()[1]	= 0.000000E+00;
	
	xs->getScattering()[0][0] = 0.000000E+00;
	xs->getScattering()[0][1] = 0.000000E+00;
	xs->getScattering()[1][0] = 2.645540e-02;
	xs->getScattering()[1][0] = 0.000000E+00;
	
	crossSections.push_back(xs);
}

