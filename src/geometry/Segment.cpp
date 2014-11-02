/*
 * Segment.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jiyoon
 */

#include "Segment.h"

int Segment::count = 0;

Segment::Segment(SubRegionType& sub, double length) :
	subRegion(sub), length(length) {

	Segment::count++;
}

Segment::~Segment() {
	// TODO Auto-generated destructor stub
}


