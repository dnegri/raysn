/*
 * QuadratureSet.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jiyoon
 */

#include "QuadratureSet.h"

QuadratureSet::QuadratureSet(int nPolarAngles) {

	this->nPolarAngles = nPolarAngles;

	this->angles  = new double[this->nPolarAngles];
	this->weights = new double[this->nPolarAngles];
	this->sins	  = new double[this->nPolarAngles];

	if (nPolarAngles == 1) {
		sins[0]	   = 0.798184;
		weights[0] = 1.0;
	}
	else if (nPolarAngles == 2) {
		sins[0]	   = 0.363900;
		sins[1]	   = 0.899900;
		weights[0] = 0.212854;
		weights[1] = 0.787146;
	}
	else if (nPolarAngles == 3) {
		sins[0]	   = 0.1187086;
		sins[1]	   = 0.4403554;
		sins[2]	   = 0.9057904;
		weights[0] = 0.0244934;
		weights[1] = 0.2184170;
		weights[2] = 0.7570896;
//		sins[0]	   = 0.166648;
//		sins[1]	   = 0.537707;
//		sins[2]	   = 0.932954;
//		weights[0] = 0.046233;
//		weights[1] = 0.283619;
//		weights[2] = 0.670148;
	}
	else {

	}
}

QuadratureSet::~QuadratureSet() {
	delete [] angles;
	delete [] weights;
	delete [] sins;
}


