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
#include "XSLibrary.h"
#include "SubRegion.h"

class Region  : public RaysnClass {
private:
	int							energyGroup;
	const RegionType*			type;
	const CrossSection*			crossSection;
	double *					flux;

	boost::ptr_vector<SubRegion> subRegions;

public:
	Region(int energyGroup, const RegionType& type);
	virtual ~Region();

	double calculateFissionSource();
	void   calculateSource(int group, double reigv);
	void   addSelfScattering(int group);
	void   clearOneGroupFlux(int group);
	void   makeOneGroupFlux(int group);
	void   calculateFlux();

	const CrossSection& getCrossSection() const {
		return *crossSection;
	}

	void updateCrossSection(const XSLibrary& xsl);


	SubRegion& getSubRegion(int index)  {
		return subRegions.at(index);
	}
	
	boost::ptr_vector<SubRegion>& getSubRegions()  {
		return subRegions;
	}

	double getFlux(int group) {
		return flux[group];
	}
	
	double getFissionSouce(int ig);
	double getRemovalTerm(int ig);
	double getScatteringSource(int ig);
	
	const RegionType& getType() {
		return *type;
	}
	
	void showResult();
};

#endif /* SOLUTION_REGION_H_ */
