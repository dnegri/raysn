/*
 * SubRegion.h
 *
 *  Created on: Oct 10, 2014
 *      Author: jiyoon
 */

#ifndef SUBREGION_H_
#define SUBREGION_H_

#include "../pch.h"
#include "Line.h"



class RegionType;

class SubRegionType {

private:
	int						index;
	double					volume;
	double					segmentVolume = 0.0;
	RegionType&				region;
	boost::ptr_vector<Line> edges;

public:
	SubRegionType(RegionType& region);
	virtual ~SubRegionType();

	void addEdge(Line& edge);

	boost::ptr_vector<Line>& getEdges() {
		return edges;
	}

	const RegionType& getRegion() const {
		return region;
	}

	double getVolume() const {
		return volume;
	}

	void setVolume(double volume) {
		this->volume = volume;
	}
	
	void addSegmentVolume(double segmentVolume) {
		this->segmentVolume += segmentVolume;
	}

	double getSegmentFactor() const {
		return volume / segmentVolume;
	}

	int getIndex() const {
		return index;
	}

	void setIndex(int index) {
		this->index = index;
	}
};



#endif /* SUBREGION_H_ */
