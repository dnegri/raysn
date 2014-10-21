/*
 * Cell.h
 *
 *  Created on: Oct 13, 2014
 *      Author: jiyoon
 */

#ifndef CELL_H_
#define CELL_H_

#include "../pch.h"
#include "../geometry/FuelCellType.h"
#include "../geometry/CellTypeSurface.h"
#include "../xs/XSLibrary.h"
#include "Region.h"
#include "CellSurface.h"

class Cell {
private:
	int x, y;
	int initialNEWS = NORTH;
	XSLibrary* xsl;
	FuelCellType* type;
	boost::ptr_vector<Region> regions;
	CellSurface* surface[NEWS];
public:
	Cell(int x, int y, FuelCellType& type, XSLibrary& xsl);
	virtual ~Cell();

	void solveOuter(int nout, int nInner);
	void solveInner(int nInner, double reigv);
	void clearOneGroupFlux(int group);
	void makeOneGroupFlux(int group);
	double calculateFissionSource();
	void updateCrossSection();

	const boost::ptr_vector<Region>& getRegions() const {
		return regions;
	}

	int getX() {
		return x;
	}
	
	int getY() {
		return y;
	}
	
};

#endif /* CELL_H_ */
