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

//	(*xs->getTransport()) 	= {2.70653E-02,  7.233540e-02};
	xs->getTransport()[0] = 2.70653E-02;
//	xs->getNuFission() 	= {5.576590e-03, 9.986290e-02};
//	xs->getChi() 		= {1.000000E+00, 0.000000E+00};
//	xs->getScattering() = {{0.000000E+00,0.000000E+00}, {1.800400e-02, 0.000000E+00}} ;
//
//	crossSections.push_back(xs);
//
//	xs = new CrossSection(*this);
//
//	xs->getTransport() 	= {2.682870E-02, 1.772150e-02};
//	xs->getNuFission() 	= {0.000000E+00, 0.000000E+00};
//	xs->getChi() 		= {1.000000E+00, 0.000000E+00};
//	xs->getScattering() = {{0.000000E+00,0.000000E+00}, {2.645540e-02, 0.000000E+00}} ;

	crossSections.push_back(xs);
}

