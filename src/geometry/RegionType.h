/*
 * Region.h
 *
 *  Created on: Oct 10, 2014
 *      Author: jiyoon
 */

#ifndef REGION_H_
#define REGION_H_

#include "../pch.h"
#include "SubRegionType.h"



class RegionType {

private:
	int								 index;
	double							 volume;
	boost::ptr_vector<SubRegionType> subRegions;

public:
	RegionType();
	virtual ~RegionType();

	void addSubRegion(SubRegionType* region);

	boost::ptr_vector<SubRegionType>& getSubRegions() {
		return subRegions;
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



#endif /* REGION_H_ */
