/*
 * Region.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jiyoon
 */

#include "RegionType.h"



RegionType::RegionType() {
	// TODO Auto-generated constructor stub

}

RegionType::~RegionType() {
	// TODO Auto-generated destructor stub
}

void RegionType::addSubRegion(SubRegionType* region) {
	subRegions.push_back(region);
}


