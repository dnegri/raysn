/*
 * SubRegion.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jiyoon
 */

#include "SubRegionType.h"
#include "RegionType.h"



SubRegionType::SubRegionType(RegionType& region) : region(region) {
	region.addSubRegion(this);
}

SubRegionType::~SubRegionType() {
}

void SubRegionType::addEdge(Line& edge) {
	edges.push_back(&edge);
	edge.addSubRegion(*this);
}


