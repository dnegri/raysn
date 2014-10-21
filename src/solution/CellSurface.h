/*
 * CellSurface.h
 *
 *  Created on: Oct 17, 2014
 *      Author: jiyoon
 */

#ifndef SOLUTION_CELLSURFACE_H_
#define SOLUTION_CELLSURFACE_H_

#include "../geometry/FuelCellType.h"
#include "../xs/XSLibrary.h"

class CellSurface {
private:
	int					   nAngles;
	int					   nPolar;
	std::vector<double**>* angFlux;

public:
	CellSurface(FuelCellType& type, XSLibrary& xsl, int dirxy);
	virtual ~CellSurface();

	std::vector<double**>& getAngFlux(int iAngle) {
		return angFlux[iAngle];
	}
};

#endif /* SOLUTION_CELLSURFACE_H_ */
