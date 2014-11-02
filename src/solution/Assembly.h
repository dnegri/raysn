/*
 * Assembly.h
 *
 *  Created on: Oct 17, 2014
 *      Author: jiyoon
 */

#ifndef SOLUTION_ASSEMBLY_H_
#define SOLUTION_ASSEMBLY_H_

#include "../pch.h"
#include "Cell.h"
#include "CellSurface.h"

class Assembly {
private:
	int x;
	int y;
	int nxc;
	int nyc;
	boost::ptr_vector<CellSurface> 	surfaces;
	boost::ptr_map<int, Cell> 		cells;
	
	
private:
	int generateKey(int x, int y);
	
public:
	Assembly();
	Assembly(int x, int y, int nxc, int nyc);
	virtual ~Assembly();
	
	void construct(boost::ptr_vector<CellType>& cellTypes, XSLibrary& xsl);
	void solve();
	
	int getX() const {return x;}
	int getY() const {return y;}
	
	void addCell(Cell& cell);
	Cell& getCell(int x, int y);
	
	void updateCrossSection();
	
	
	
	
};

#endif /* SOLUTION_ASSEMBLY_H_ */
