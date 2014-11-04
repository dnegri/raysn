/*
 * XSLibrary.h
 *
 *  Created on: Oct 17, 2014
 *      Author: jiyoon
 */

#ifndef XS_XSLIBRARY_H_
#define XS_XSLIBRARY_H_
#include "../pch.h"
#include "CrossSection.h"

class XSLibrary  : public RaysnClass {
private:
	int								energyGroup;
	boost::ptr_vector<CrossSection> crossSections;

public:
	XSLibrary();
	virtual ~XSLibrary();

	void initialize();

	CrossSection& getCrossSection(int index) {
		return crossSections.at(index);
	}

	int getEnergyGroup() const {
		return energyGroup;
	}
};


#endif /* XS_XSLIBRARY_H_ */
