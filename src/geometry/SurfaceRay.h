/*
 * SurfaceToSurfaceRay.h
 *
 *  Created on: Oct 13, 2014
 *      Author: jiyoon
 */

#ifndef SURFACERAY_H_
#define SURFACERAY_H_

#include "../pch.h"
#include "Segment.h"



class SurfaceRay {
private:
	double					   length;
	boost::ptr_vector<Segment> segments;

public:
	SurfaceRay();
	virtual ~SurfaceRay();

	double getLength() const {
		return length;
	}

	void setLength(double length) {
		this->length = length;
	}

	boost::ptr_vector<Segment>& getSegments() {
		return segments;
	}

	void addSegment(Segment& segment);
};



#endif /* SURFACERAY_H_ */
