/*
 * Region.h
 *
 *  Created on: Oct 17, 2014
 *      Author: jiyoon
 */

#ifndef SOLUTION_REGION_H_
#define SOLUTION_REGION_H_
#include "../pch.h"
#include "../geometry/RegionType.h"
#include "../xs/CrossSection.h"
#include "SubRegion.h"

class Region {
private:
	RegionType* type;
	CrossSection* crossSection;
	double * flux;

	boost::ptr_vector<SubRegion> subRegions;

public:
	Region(const int energyGroup, RegionType& type);
	virtual ~Region();

	double calculateFissionSource();
	void calculateSource(int group, double reigv);
	void addSelfScattering(int group);
	void clearOneGroupFlux(int group);
	void makeOneGroupFlux(int group);
	
	CrossSection& getCrossSection() {
		return *crossSection;
	}

	SubRegion& getSubRegion(int index)  {
		return subRegions.at(index);
	}
};

#endif /* SOLUTION_REGION_H_ */
