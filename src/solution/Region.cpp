/*
 * Region.cpp
 *
 *  Created on: Oct 17, 2014
 *      Author: jiyoon
 */

#include "Region.h"

Region::Region(int energyGroup, const RegionType& type) {

	this->type = &type;
	this->energyGroup = energyGroup;

	flux		 = new double[energyGroup];
	crossSection = new CrossSection(energyGroup);

	for(const SubRegionType& subRegionType : type.getSubRegions()) {
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

void Region::showResult() {
	logger.info("REGION(%2i) FISSION SOURCE : %12.5e", type->getIndex(), calculateFissionSource());

	for(SubRegion& sub : subRegions ) {
		sub.showResult();
	}

}

void Region::calculateFlux() {
	for(int ig=0;ig<energyGroup;ig++) {
		flux[ig]=0;
		for(SubRegion& sub : subRegions ) {
			flux[ig] += sub.getFlux(ig)*sub.getType().getVolume();
		}
		flux[ig] /= type->getVolume();
	}
	
}

double Region::getFissionSouce(int ig) {
	
	double fission = 0.0;
	for(int g=0;g<energyGroup;g++) {
		fission += flux[g] * crossSection->getNuFission()[g];
	}
	
	return crossSection->getChi()[ig]*fission*type->getVolume();
}
double Region::getRemovalTerm(int ig) {
	
	return crossSection->getTransport()[ig]*flux[ig]*type->getVolume();
}
double Region::getScatteringSource(int ig) {
	double scattering = 0.0;
	for(int g=0;g<energyGroup;g++) {
		scattering += flux[g] * crossSection->getScattering()[ig][g];
	}
	
	return scattering*type->getVolume();
}


void Region::updateCrossSection(const XSLibrary& xsl) {

	const CrossSection& crossSection = xsl.getCrossSection(type->getXSName());
	
	this->crossSection = &crossSection;
}