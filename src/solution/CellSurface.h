/*
 * CellSurface.h
 *
 *  Created on: Oct 17, 2014
 *      Author: jiyoon
 */

#ifndef SOLUTION_CELLSURFACE_H_
#define SOLUTION_CELLSURFACE_H_

#include "../pch.h"
#include "../geometry/CellTypeSurface.h"
#include "../geometry/CellType.h"
#include "../xs/XSLibrary.h"

typedef boost::multi_array<std::vector<double>, 4> SurfaceAngularFlux;

class CellSurface {
private:
	boost::ptr_vector<CellTypeSurface> types;
	SurfaceAngularFlux* angularFlux;
//	boost::ptr_vector<boost::ptr_vector<boost::ptr_vector<boost::ptr_vector<double*>>>> angFlux; //group, angle, point, islope, polar

public:
	CellSurface();
	CellSurface(CellType& type, XSLibrary& xsl, int dirxy);
	virtual ~CellSurface();

	double getAngFlux(int igroup, AzimuthalAngle& angle, SurfaceRayPoint& point, int islope, int ipolar);
	void setAngFlux(int igroup, AzimuthalAngle& angle, SurfaceRayPoint& point, int islope, int ipolar, double angFlux);
	
	CellTypeSurface& getType(int selfneib) {
		return types.at(selfneib);
	}
	
	void setType(int selfneib, CellTypeSurface& type) {
		types.replace(selfneib, &type);
	}
};

#endif /* SOLUTION_CELLSURFACE_H_ */
