/*
 * CrossSection.h
 *
 *  Created on: Oct 17, 2014
 *      Author: jiyoon
 */

#ifndef XS_CROSSSECTION_H_
#define XS_CROSSSECTION_H_
#include "../pch.h"


class CrossSection  : public RaysnClass {
private:
	int		 energyGroup;
	double*	 nuFission;
	double*	 total;
	double*	 transport;
	double*	 chi;
	double** scattering;

public:
	CrossSection(const int energyGroup);
	virtual ~CrossSection();

	void operator=(const CrossSection& crossSection);

	double* getChi() const {
		return chi;
	}

	int getEnergyGroup() const {
		return energyGroup;
	}

	double* getNuFission() const {
		return nuFission;
	}

	double** getScattering() const {
		return scattering;
	}

	double* getTotal() const {
		return total;
	}

	double* getTransport() const {
		return transport;
	}
};


#endif /* XS_CROSSSECTION_H_ */
