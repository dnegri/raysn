//
//  C5G7Libary.cpp
//  raysn
//
//  Created by Jooil Yoon on 11/17/14.
//  Copyright (c) 2014 Jooil Yoon. All rights reserved.
//

#include "C5G7Library.h"


C5G7Library::C5G7Library() {
}
C5G7Library::~C5G7Library() {
}

void C5G7Library::initialize() {
	energyGroup = 7;
	
	this->crossSections.insert("UO2"	, getUO2XS());
	this->crossSections.insert("MOX87"	, getMOX87());
	this->crossSections.insert("MOX70"	, getMOX70());
	this->crossSections.insert("MOX43"	, getMOX43());
	this->crossSections.insert("GT"		, getGuideTubeXS());
	this->crossSections.insert("MOD"	, getModeratorXS());
}


CrossSection* C5G7Library::getUO2XS() {

	CrossSection* xs = new CrossSection(energyGroup);
	
	int g = 0;
	xs->getNuFission()[g++] = 2.005998E-02;
	xs->getNuFission()[g++] = 2.027303E-03;
	xs->getNuFission()[g++] = 1.570599E-02;
	xs->getNuFission()[g++] = 4.518301E-02;
	xs->getNuFission()[g++] = 4.334208E-02;
	xs->getNuFission()[g++] = 2.020901E-01;
	xs->getNuFission()[g++] = 5.257105E-01;
									
	g = 0;
	xs->getTransport()[g++] = 1.77949E-01;
	xs->getTransport()[g++] = 3.29805E-01;
	xs->getTransport()[g++] = 4.80388E-01;
	xs->getTransport()[g++] = 5.54367E-01;
	xs->getTransport()[g++] = 3.11801E-01;
	xs->getTransport()[g++] = 3.95168E-01;
	xs->getTransport()[g++] = 5.64406E-01;

	g = 0;
	xs->getChi()[g++] = 5.87910E-01;
	xs->getChi()[g++] = 4.11760E-01;
	xs->getChi()[g++] = 3.39060E-04;
	xs->getChi()[g++] = 1.17610E-07;
	xs->getChi()[g++] = 0.00000E+00;
	xs->getChi()[g++] = 0.00000E+00;
	xs->getChi()[g++] = 0.00000E+00;

	int ge = 0;
	int gs = 0;
	xs->getScattering()[ge++][gs] = 1.27537E-01;
	xs->getScattering()[ge++][gs] = 4.23780E-02;
	xs->getScattering()[ge++][gs] = 9.43740E-06;
	xs->getScattering()[ge++][gs] = 5.51630E-09;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	
	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 3.24456E-01;
	xs->getScattering()[ge++][gs] = 1.63140E-03;
	xs->getScattering()[ge++][gs] = 3.14270E-09;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;

	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 4.50940E-01;
	xs->getScattering()[ge++][gs] = 2.67920E-03;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;

	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 4.52565E-01;
	xs->getScattering()[ge++][gs] = 5.56640E-03;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;

	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 1.25250E-04;
	xs->getScattering()[ge++][gs] = 2.71401E-01;
	xs->getScattering()[ge++][gs] = 1.02550E-02;
	xs->getScattering()[ge++][gs] = 1.00210E-08;

	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 1.29680E-03;
	xs->getScattering()[ge++][gs] = 2.65802E-01;
	xs->getScattering()[ge++][gs] = 1.68090E-02;

	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 8.54580E-03;
	xs->getScattering()[ge++][gs] = 2.73080E-01;
	
	return xs;
}

CrossSection* C5G7Library::getModeratorXS() {

	CrossSection* xs = new CrossSection(energyGroup);
	
	int g = 0;
	xs->getNuFission()[g++] = 0.0;
	xs->getNuFission()[g++] = 0.0;
	xs->getNuFission()[g++] = 0.0;
	xs->getNuFission()[g++] = 0.0;
	xs->getNuFission()[g++] = 0.0;
	xs->getNuFission()[g++] = 0.0;
	xs->getNuFission()[g++] = 0.0;
									
	g = 0;
	xs->getTransport()[g++] = 1.59206E-01;
	xs->getTransport()[g++] = 4.12970E-01;
	xs->getTransport()[g++] = 5.90310E-01;
	xs->getTransport()[g++] = 5.84350E-01;
	xs->getTransport()[g++] = 7.18000E-01;
	xs->getTransport()[g++] = 1.25445E+00;
	xs->getTransport()[g++] = 2.65038E+00;

	g = 0;
	xs->getChi()[g++] = 0.00000E+00;
	xs->getChi()[g++] = 0.00000E+00;
	xs->getChi()[g++] = 0.00000E+00;
	xs->getChi()[g++] = 0.00000E+00;
	xs->getChi()[g++] = 0.00000E+00;
	xs->getChi()[g++] = 0.00000E+00;
	xs->getChi()[g++] = 0.00000E+00;

	int ge = 0;
	int gs = 0;
	xs->getScattering()[ge++][gs] = 4.44777E-02;
	xs->getScattering()[ge++][gs] = 1.13400E-01;
	xs->getScattering()[ge++][gs] = 7.23470E-04;
	xs->getScattering()[ge++][gs] = 3.74990E-06;
	xs->getScattering()[ge++][gs] = 5.31840E-08;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	
	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 2.82334E-01;
	xs->getScattering()[ge++][gs] = 1.29940E-01;
	xs->getScattering()[ge++][gs] = 6.23400E-04;
	xs->getScattering()[ge++][gs] = 4.80020E-05;
	xs->getScattering()[ge++][gs] = 7.44860E-06;
	xs->getScattering()[ge++][gs] = 1.04550E-06;

	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 3.45256E-01;
	xs->getScattering()[ge++][gs] = 2.24570E-01;
	xs->getScattering()[ge++][gs] = 1.69990E-02;
	xs->getScattering()[ge++][gs] = 2.64430E-03;
	xs->getScattering()[ge++][gs] = 5.03440E-04;

	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 9.10284E-02;
	xs->getScattering()[ge++][gs] = 4.15510E-01;
	xs->getScattering()[ge++][gs] = 6.37320E-02;
	xs->getScattering()[ge++][gs] = 1.21390E-02;

	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 7.14370E-05;
	xs->getScattering()[ge++][gs] = 1.39138E-01;
	xs->getScattering()[ge++][gs] = 5.11820E-01;
	xs->getScattering()[ge++][gs] = 6.12290E-02;

	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 2.21570E-03;
	xs->getScattering()[ge++][gs] = 6.99913E-01;
	xs->getScattering()[ge++][gs] = 5.37320E-01;

	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 1.32440E-01;
	xs->getScattering()[ge++][gs] = 2.48070E+00;
	
	return xs;
}

CrossSection* C5G7Library::getGuideTubeXS() {

	CrossSection* xs = new CrossSection(energyGroup);

	int g = 0;
	xs->getNuFission()[g++] = 0.0;
	xs->getNuFission()[g++] = 0.0;
	xs->getNuFission()[g++] = 0.0;
	xs->getNuFission()[g++] = 0.0;
	xs->getNuFission()[g++] = 0.0;
	xs->getNuFission()[g++] = 0.0;
	xs->getNuFission()[g++] = 0.0;
									
	g = 0;
	xs->getTransport()[g++] = 1.26032E-01;
	xs->getTransport()[g++] = 2.93160E-01;
	xs->getTransport()[g++] = 2.84240E-01;
	xs->getTransport()[g++] = 2.80960E-01;
	xs->getTransport()[g++] = 3.34440E-01;
	xs->getTransport()[g++] = 5.65640E-01;
	xs->getTransport()[g++] = 1.17215E+00;

	g = 0;
	xs->getChi()[g++] = 0.00000E+00;
	xs->getChi()[g++] = 0.00000E+00;
	xs->getChi()[g++] = 0.00000E+00;
	xs->getChi()[g++] = 0.00000E+00;
	xs->getChi()[g++] = 0.00000E+00;
	xs->getChi()[g++] = 0.00000E+00;
	xs->getChi()[g++] = 0.00000E+00;

	int ge = 0;
	int gs = 0;
	xs->getScattering()[ge++][gs] = 6.61659E-02;
	xs->getScattering()[ge++][gs] = 5.90700E-02;
	xs->getScattering()[ge++][gs] = 2.83340E-04;
	xs->getScattering()[ge++][gs] = 1.46220E-06;
	xs->getScattering()[ge++][gs] = 2.06420E-08;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;

	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 2.40377E-01;
	xs->getScattering()[ge++][gs] = 5.24350E-02;
	xs->getScattering()[ge++][gs] = 2.49900E-04;
	xs->getScattering()[ge++][gs] = 1.92390E-05;
	xs->getScattering()[ge++][gs] = 2.98750E-06;
	xs->getScattering()[ge++][gs] = 4.21400E-07;

	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 1.83297E-01;
	xs->getScattering()[ge++][gs] = 9.23970E-02;
	xs->getScattering()[ge++][gs] = 6.94460E-03;
	xs->getScattering()[ge++][gs] = 1.08030E-03;
	xs->getScattering()[ge++][gs] = 2.05670E-04;

	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 7.88511E-02;
	xs->getScattering()[ge++][gs] = 1.70140E-01;
	xs->getScattering()[ge++][gs] = 2.58810E-02;
	xs->getScattering()[ge++][gs] = 4.92970E-03;

	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 3.73330E-05;
	xs->getScattering()[ge++][gs] = 9.97372E-02;
	xs->getScattering()[ge++][gs] = 2.06790E-01;
	xs->getScattering()[ge++][gs] = 2.44780E-02;

	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 9.17260E-04;
	xs->getScattering()[ge++][gs] = 3.16765E-01;
	xs->getScattering()[ge++][gs] = 2.38770E-01;

	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 4.97920E-02;
	xs->getScattering()[ge++][gs] = 1.09912E+00;

	
	return xs;
}

CrossSection* C5G7Library::getMOX87() {

	CrossSection* xs = new CrossSection(energyGroup);
	
	int g = 0;
	xs->getNuFission()[g++] = 8.67209E-03 * 2.90426E+00;
	xs->getNuFission()[g++] = 1.62426E-03 * 2.91795E+00;
	xs->getNuFission()[g++] = 1.02716E-02 * 2.86986E+00;
	xs->getNuFission()[g++] = 3.90447E-02 * 2.87491E+00;
	xs->getNuFission()[g++] = 1.92576E-02 * 2.87175E+00;
	xs->getNuFission()[g++] = 3.74888E-01 * 2.86752E+00;
	xs->getNuFission()[g++] = 4.30599E-01 * 2.87808E+00;

	g = 0;
	xs->getTransport()[g++] = 1.83045E-01;
	xs->getTransport()[g++] = 3.36705E-01;
	xs->getTransport()[g++] = 5.00507E-01;
	xs->getTransport()[g++] = 6.06174E-01;
	xs->getTransport()[g++] = 5.02754E-01;
	xs->getTransport()[g++] = 9.21028E-01;
	xs->getTransport()[g++] = 9.55231E-01;
	
	g = 0;
	xs->getChi()[g++] = 5.87910E-01;
	xs->getChi()[g++] = 4.11760E-01;
	xs->getChi()[g++] = 3.39060E-04;
	xs->getChi()[g++] = 1.17610E-07;
	xs->getChi()[g++] = 0.00000E+00;
	xs->getChi()[g++] = 0.00000E+00;
	xs->getChi()[g++] = 0.00000E+00;
	
	int ge = 0;
	int gs = 0;
	xs->getScattering()[ge++][gs] = 1.31504E-01;
	xs->getScattering()[ge++][gs] = 4.20460E-02;
	xs->getScattering()[ge++][gs] = 8.69720E-06;
	xs->getScattering()[ge++][gs] = 5.19380E-09;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	
	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 3.30403E-01;
	xs->getScattering()[ge++][gs] = 1.64630E-03;
	xs->getScattering()[ge++][gs] = 2.60060E-09;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	
	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 4.61792E-01;
	xs->getScattering()[ge++][gs] = 2.47490E-03;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	
	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 4.68021E-01;
	xs->getScattering()[ge++][gs] = 5.43300E-03;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	
	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 1.85970E-04;
	xs->getScattering()[ge++][gs] = 2.85771E-01;
	xs->getScattering()[ge++][gs] = 8.39730E-03;
	xs->getScattering()[ge++][gs] = 8.92800E-09;
	
	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 2.39160E-03;
	xs->getScattering()[ge++][gs] = 2.47614E-01;
	xs->getScattering()[ge++][gs] = 1.23220E-02;
	
	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 8.96810E-03;
	xs->getScattering()[ge++][gs] = 2.56093E-01;
	
	return xs;
}


CrossSection* C5G7Library::getMOX70() {

	CrossSection* xs = new CrossSection(energyGroup);
	

	int g = 0;
	xs->getNuFission()[g++] = 8.25446E-03 * 2.88498E+00;
	xs->getNuFission()[g++] = 1.32565E-03 * 2.91079E+00;
	xs->getNuFission()[g++] = 8.42156E-03 * 2.86574E+00;
	xs->getNuFission()[g++] = 3.28730E-02 * 2.87063E+00;
	xs->getNuFission()[g++] = 1.59636E-02 * 2.86714E+00;
	xs->getNuFission()[g++] = 3.23794E-01 * 2.86658E+00;
	xs->getNuFission()[g++] = 3.62803E-01 * 2.87539E+00;

	g = 0;
	xs->getTransport()[g++] = 1.81323E-01;
	xs->getTransport()[g++] = 3.34368E-01;
	xs->getTransport()[g++] = 4.93785E-01;
	xs->getTransport()[g++] = 5.91216E-01;
	xs->getTransport()[g++] = 4.74198E-01;
	xs->getTransport()[g++] = 8.33601E-01;
	xs->getTransport()[g++] = 8.53603E-01;
	
	g = 0;
	xs->getChi()[g++] = 5.87910E-01;
	xs->getChi()[g++] = 4.11760E-01;
	xs->getChi()[g++] = 3.39060E-04;
	xs->getChi()[g++] = 1.17610E-07;
	xs->getChi()[g++] = 0.00000E+00;
	xs->getChi()[g++] = 0.00000E+00;
	xs->getChi()[g++] = 0.00000E+00;
	
	int ge = 0;
	int gs = 0;
	xs->getScattering()[ge++][gs] = 1.30457E-01;
	xs->getScattering()[ge++][gs] = 4.17920E-02;
	xs->getScattering()[ge++][gs] = 8.51050E-06;
	xs->getScattering()[ge++][gs] = 5.13290E-09;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	
	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 3.28428E-01;
	xs->getScattering()[ge++][gs] = 1.64360E-03;
	xs->getScattering()[ge++][gs] = 2.20170E-09;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;

	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 4.58371E-01;
	xs->getScattering()[ge++][gs] = 2.53310E-03;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;

	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 4.63709E-01;
	xs->getScattering()[ge++][gs] = 5.47660E-03;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;

	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 1.76190E-04;
	xs->getScattering()[ge++][gs] = 2.82313E-01;
	xs->getScattering()[ge++][gs] = 8.72890E-03;
	xs->getScattering()[ge++][gs] = 9.00160E-09;

	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 2.27600E-03;
	xs->getScattering()[ge++][gs] = 2.49751E-01;
	xs->getScattering()[ge++][gs] = 1.31140E-02;
	
	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 8.86450E-03;
	xs->getScattering()[ge++][gs] = 2.59529E-01;
	
	return xs;
}


CrossSection* C5G7Library::getMOX43() {

	CrossSection* xs = new CrossSection(energyGroup);
	

	int g = 0;
	xs->getNuFission()[g++] = 7.62704E-03 * 2.85209E+00;
	xs->getNuFission()[g++] = 8.76898E-04 * 2.89099E+00;
	xs->getNuFission()[g++] = 5.69835E-03 * 2.85486E+00;
	xs->getNuFission()[g++] = 2.28872E-02 * 2.86073E+00;
	xs->getNuFission()[g++] = 1.07635E-02 * 2.85447E+00;
	xs->getNuFission()[g++] = 2.32757E-01 * 2.86415E+00;
	xs->getNuFission()[g++] = 2.48968E-01 * 2.86780E+00;

	g = 0;
	xs->getTransport()[g++] = 1.78731E-01;
	xs->getTransport()[g++] = 3.30849E-01;
	xs->getTransport()[g++] = 4.83772E-01;
	xs->getTransport()[g++] = 5.66922E-01;
	xs->getTransport()[g++] = 4.26227E-01;
	xs->getTransport()[g++] = 6.78997E-01;
	xs->getTransport()[g++] = 6.82852E-01;
	
	g = 0;
	xs->getChi()[g++] = 5.87910E-01;
	xs->getChi()[g++] = 4.11760E-01;
	xs->getChi()[g++] = 3.39060E-04;
	xs->getChi()[g++] = 1.17610E-07;
	xs->getChi()[g++] = 0.00000E+00;
	xs->getChi()[g++] = 0.00000E+00;
	xs->getChi()[g++] = 0.00000E+00;
	
	int ge = 0;
	int gs = 0;
	xs->getScattering()[ge++][gs] = 1.28876E-01;
	xs->getScattering()[ge++][gs] = 4.14130E-02;
	xs->getScattering()[ge++][gs] = 8.22900E-06;
	xs->getScattering()[ge++][gs] = 5.04050E-09;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	
	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 3.25452E-01;
	xs->getScattering()[ge++][gs] = 1.63950E-03;
	xs->getScattering()[ge++][gs] = 1.59820E-09;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	
	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 4.53188E-01;
	xs->getScattering()[ge++][gs] = 2.61420E-03;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	
	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 4.57173E-01;
	xs->getScattering()[ge++][gs] = 5.53940E-03;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	
	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 1.60460E-04;
	xs->getScattering()[ge++][gs] = 2.76814E-01;
	xs->getScattering()[ge++][gs] = 9.31270E-03;
	xs->getScattering()[ge++][gs] = 9.16560E-09;
	
	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 2.00510E-03;
	xs->getScattering()[ge++][gs] = 2.52962E-01;
	xs->getScattering()[ge++][gs] = 1.48500E-02;
	
	gs++;
	ge = 0;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 0.00000E+00;
	xs->getScattering()[ge++][gs] = 8.49480E-03;
	xs->getScattering()[ge++][gs] = 2.65007E-01;

	
	return xs;
}
