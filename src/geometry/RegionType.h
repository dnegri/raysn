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



class RegionType  : public RaysnClass {

private:
	std::string						 xsName;
	int								 index;
	double							 volume;
	boost::ptr_vector<SubRegionType> subRegions;

public:
	RegionType();
	virtual ~RegionType();

	void addSubRegion(SubRegionType* region);

	const boost::ptr_vector<SubRegionType>& getSubRegions() const {
		return subRegions;
	}

	boost::ptr_vector<SubRegionType>& getSubRegions() {
		return subRegions;
	}

	double getVolume() const {
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
	
	void setXSName(const std::string xsName) {
		this->xsName = xsName;
	}
	
	const std::string& getXSName() const {
		return this->xsName;
	}
	
};



#endif /* REGION_H_ */
