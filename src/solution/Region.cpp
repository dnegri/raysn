/*
 * Region.cpp
 *
 *  Created on: Oct 17, 2014
 *      Author: jiyoon
 */

#include "Region.h"

Region::Region(const int energyGroup, RegionType& type) {

	this->type = &type;

	flux = new double[energyGroup];
	crossSection = new CrossSection(energyGroup);

	for(SubRegionType& subRegionType : type.getSubRegions()) {
		SubRegion* subRegion = new SubRegion(energyGroup, subRegionType);
		subRegions.push_back(subRegion);
	}
}

Region::~Region() {
	// TODO Auto-generated destructor stub
}

double Region::calculateFissionSource() {
	double fissionSource = 0.0;
	for(SubRegion& sub : subRegions ) {
		fissionSource+=sub.calculateFissionSource(*crossSection);
	}

	return fissionSource;
}

void Region::calculateSource(int group, double reigv) {
	for(SubRegion& sub : subRegions ) {
		sub.calculateSource(*crossSection, group, reigv);
	}

}

void Region::addSelfScattering(int group) {
	for(SubRegion& sub : subRegions ) {
		sub.addSelfScattering(*crossSection, group);
	}

}

void Region::clearOneGroupFlux(int group) {
	for(SubRegion& sub : subRegions ) {
		sub.clearOneGroupFlux(group);
	}
}

void Region::makeOneGroupFlux(int group) {
	for(SubRegion& sub : subRegions ) {
		sub.makeOneGroupFlux(*crossSection, group);
	}
}
