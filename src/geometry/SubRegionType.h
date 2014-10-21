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
	RegionType&				region;
	boost::ptr_vector<Line> edges;

public:
	SubRegionType(RegionType& region);
	virtual ~SubRegionType();

	void addEdge(Line& edge);

	boost::ptr_vector<Line>& getEdges() {
		return edges;
	}

	RegionType& getRegion() {
		return region;
	}

	double getVolume() {
		return volume;
	}

	void setVolume(double volume) {
		this->volume = volume;
	}

	int getIndex() const {
		return index;
	}

	void setIndex(int index) {
		this->index = index;
	}
};



#endif /* SUBREGION_H_ */
