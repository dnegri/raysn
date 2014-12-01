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
protected:
	int								energyGroup;
	boost::ptr_map<const std::string, CrossSection> crossSections;

public:
	XSLibrary();
	virtual ~XSLibrary();

	virtual void initialize();

	const CrossSection& getCrossSection(const std::string key) const {
		return crossSections.at(key);
	}

	int getEnergyGroup() const {
		return energyGroup;
	}
};


#endif /* XS_XSLIBRARY_H_ */
