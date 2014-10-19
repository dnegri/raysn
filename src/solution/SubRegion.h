/*
 * SubRegion.h
 *
 *  Created on: Oct 17, 2014
 *      Author: jiyoon
 */

#ifndef SOLUTION_SUBREGION_H_
#define SOLUTION_SUBREGION_H_
#include "../pch.h"
#include "../geometry/SubRegionType.h"
#include "../xs/CrossSection.h"

class SubRegion {
private:
	SubRegionType* type;
	double * flux;
	double * source;
	double fissionSource;

public:
	SubRegion(int energyGroup, SubRegionType& type);
	virtual ~SubRegion();

	void calculateSource(const CrossSection& xs, int group, double eigv);
	double calculateFissionSource(const CrossSection& xs);
	void addSelfScattering(const CrossSection& xs, int group);
	void addOneGroupFlux(int group, double flux);
	void clearOneGroupFlux(int group);
	void makeOneGroupFlux(const CrossSection& xs, int group);
	double updateFissionSource(const CrossSection& xs);
	
	double getFlux(int group) {
		return flux[group];
	}

	void setFlux(int group, double flux) {
		this->flux[group] = flux;
	}

	double getSource(int group) {
		return source[group];
	}

};

#endif /* SOLUTION_SUBREGION_H_ */
