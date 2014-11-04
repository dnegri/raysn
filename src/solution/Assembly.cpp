/*
 * Assembly.cpp
 *
 *  Created on: Oct 17, 2014
 *      Author: jiyoon
 */

#include "Assembly.h"

Assembly::Assembly() {

}
Assembly::Assembly(int x, int y, int nxc, int nyc) : x(x), y(y), nxc(nxc), nyc(nyc) {

}

Assembly::~Assembly() {
}

void Assembly::initialize() {
	for(int y=0; y<nyc; y++) {
		for(int x=0; x<nxc; x++) {
			defineCellType(x, y, 0);
		}
	}
}
void Assembly::construct(boost::ptr_vector<CellType>& cellTypes, XSLibrary& xsl) {

	CellType& cellType = cellTypes.at(0);
	
	for(int y=0; y<nyc; y++) {
		for(int x=0; x<nxc; x++) {
			int index = indexOfCellTypes[generateKey(x, y)];
			CellType& cellType = cellTypes.at(index);
			Cell* cell = new Cell(x,y,cellType, xsl);
			this->addCell(*cell);
		}
	}
	
	int index = 0;
	for(int y=0; y<nyc; y++) {
		surfaces.push_back(new CellSurface(index++, cellType, xsl, DIRY));
		for(int x=0; x<nxc; x++) {
			surfaces.push_back(new CellSurface(index++, cellType, xsl, DIRY));
		}
	}
	
	for(int x=0; x<nxc; x++) {
		surfaces.push_back(new CellSurface(index++, cellType, xsl, DIRX));
		for(int y=0; y<nyc; y++) {
			surfaces.push_back(new CellSurface(index++, cellType, xsl, DIRX));
		}
	}
	
	int idx = -1;
	for(int y=0; y<nyc; y++) {
		++idx;
		for(int x=0; x<nxc; x++) {
			Cell& cell = getCell(x, y);
			cell.setSurface(WEST, surfaces.at(idx));
			surfaces.at(idx).setType(SELF, cellType.getSurface(WEST));
			cell.setSurface(EAST, surfaces.at(++idx));
			surfaces.at(idx).setType(SELF, cellType.getSurface(EAST));
		}
	}
	
	for(int x=0; x<nxc; x++) {
		++idx;
		for(int y=0; y<nyc; y++) {
			Cell& cell = getCell(x, y);
			cell.setSurface(NORTH, surfaces.at(idx));
			surfaces.at(idx).setType(SELF, cellType.getSurface(NORTH));
			cell.setSurface(SOUTH, surfaces.at(++idx));
			surfaces.at(idx).setType(SELF, cellType.getSurface(SOUTH));
		}
	}
	
}

void Assembly::updateCrossSection() {

	for(boost::ptr_map<int,Cell>::iterator i=cells.begin(), e=cells.end(); i != e; i++) {
		i->second->updateCrossSection();
	}
}

void Assembly::solve() {
	for(int y=0; y<nyc; y++) {
	for(int x=0; x<nxc; x++) {
		Cell& cell = getCell(x, y);
		cell.solveOuter(1000, 3);
	}
	}
}

int Assembly::generateKey(int x, int y) {
	return x*1000+y;
}

void Assembly::defineCellType(int x, int y, int indexOfCellType) {
	int key = generateKey(x, y);
	indexOfCellTypes[key] = indexOfCellType;
}

void Assembly::addCell(Cell& cell) {
	int key = generateKey(cell.getX(), cell.getY());
	cells.insert(key, &cell);
}

Cell& Assembly::getCell(int x, int y) {
	int key = generateKey(x, y);
	return cells[key];
}
