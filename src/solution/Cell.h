/*
 * Cell.h
 *
 *  Created on: Oct 13, 2014
 *      Author: jiyoon
 */

#ifndef CELL_H_
#define CELL_H_

#include "../pch.h"
#include "../geometry/CellType.h"
#include "../geometry/CellTypeSurface.h"
#include "../xs/XSLibrary.h"
#include "Region.h"
#include "CellSurface.h"
#include "gnuplot-iostream.h"

class Cell  : public RaysnClass {
private:
	int						  		x, y;
	XSLibrary*				  		xsl;
	CellType*			  			type;
	boost::ptr_vector<Region> 		regions;
	boost::ptr_vector<CellSurface>  surfaces;
	boost::ptr_vector<Cell> 		neighbor;

public:
	std::vector<boost::tuple<double, double> > plotData;

public:
	Cell();
	Cell(int x, int y, CellType& type, XSLibrary& xsl);
	virtual ~Cell();

	void   solveOuter(int nout, int nInner);
	void   solveInner(int nInner, double reigv);
	void   clearOneGroupFlux(int group);
	void   makeOneGroupFlux(int group);
	double calculateFissionSource();
	void   updateCrossSection();

	void setSurface(int news, CellSurface& surface) {
		surfaces.replace(news, &surface);
	}

	CellSurface& getSurface(int news) {
		return surfaces.at(news);
	}
	
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
