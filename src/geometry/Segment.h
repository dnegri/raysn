/*
 * Segment.h
 *
 *  Created on: Oct 10, 2014
 *      Author: jiyoon
 */

#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "../pch.h"
#include "SubRegionType.h"



class Segment {
private:
	double length;
	SubRegionType& subRegion;

public:
	Segment(SubRegionType& sub, double length);
	virtual ~Segment();

	double getLength() {
		return length;
	}

	void setLength(double length) {
		this->length = length;
	}

	SubRegionType& getSubRegion() {
		return subRegion;
	}
};



#endif /* SEGMENT_H_ */
