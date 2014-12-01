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
	const XSLibrary*				xsl;
	const CellType*			  		type;
	boost::ptr_vector<Region> 		regions;
	boost::ptr_vector<CellSurface>  surfaces;
	Cell* 							neighbor[NEWS];
	double*							flux;
	
public:
	std::vector<boost::tuple<double, double> > plotData;

public:
	Cell();
	Cell(int x, int y, const CellType& type, const XSLibrary& xsl);
	virtual ~Cell();

	void   solveInner(int nInner, double reigv);
	void   clearOneGroupFlux(int group);
	void   makeOneGroupFlux(int group);
	double calculateFissionSource();
	void   updateCrossSection();
	void   calculateIncomingCurrent();
	void   calculateAverageAngularFlux();
	void   calculateFlux();
	bool   checkNodalBalance(double reigv);
	void   checkShapeFunction();
	void   generateShapeFunction();
	void   generateFunctionalAngularFlux();
	void setSurface(int news, CellSurface& surface) {
		surfaces.replace(news, &surface);
	}

	CellSurface& getSurface(int news) {
		return surfaces.at(news);
	}
	
	boost::ptr_vector<Region>& getRegions() {
		return regions;
	}
	
	void setNeighbor(int inews, Cell& neighbor) {
		this->neighbor[inews] = &neighbor;
	}

	Cell& getNeighbor(int inews) {
		return *this->neighbor[inews];
	}

	int getX() {
		return x;
	}

	int getY() {
		return y;
	}
	
	double getFlux(int ig) {
		return flux[ig];
	}
	
	
	void showResult();

};

#endif /* CELL_H_ */
