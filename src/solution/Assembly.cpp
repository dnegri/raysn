/*
 * Assembly.cpp
 *
 *  Created on: Oct 17, 2014
 *      Author: jiyoon
 */

#include "Assembly.h"
#include "MatrixVectorOperation.h"

Assembly::Assembly() {

}

Assembly::Assembly(int x, int y, const AssemblyType& type) : x(x), y(y), type(&type) {

}

Assembly::~Assembly() {
}

void Assembly::initialize() {
}

void Assembly::construct(const boost::ptr_map<const std::string, CellType>& cellTypes, const XSLibrary& xsl) {

	for(int y=0; y<type->getNYCell(); y++) {
		for(int x=0; x<type->getNXCell(); x++) {
			const std::string& cellName = type->getCellName(x, y);

			const CellType& cellType = cellTypes.at(cellName);
			Cell* cell = new Cell(x,y,cellType, xsl);
			this->addCell(*cell);
		}
	}
	
	int index = 0;
	for(int y=0; y<type->getNYCell(); y++) {
		Cell& leftmost = getCell(0, y);
		leftmost.getSurface(WEST).setBoundary(true);
		leftmost.getSurface(WEST).setIndex(index++);
		
		for(int x=0; x<type->getNXCell()-1; x++) {
			Cell& cell = getCell(x, y);
			cell.getSurface(EAST).setIndex(index++);

			Cell& eastCell = getCell(x+1, y);
			eastCell.getSurface(WEST).setIndex(index);

			cell.setNeighbor(EAST, eastCell);
			eastCell.setNeighbor(WEST, cell);
			
			cell.getSurface(EAST).setAdjoint(eastCell.getSurface(WEST));
			eastCell.getSurface(WEST).setAdjoint(cell.getSurface(EAST));
		}
		
		Cell& rightmost = getCell(type->getNXCell()-1, y);
		rightmost.getSurface(EAST).setBoundary(true);
		rightmost.getSurface(EAST).setIndex(index++);
		
	}
	
	for(int x=0; x<type->getNXCell(); x++) {
		Cell& leftmost = getCell(x, 0);
		leftmost.getSurface(NORTH).setBoundary(true);
		leftmost.getSurface(NORTH).setIndex(index++);
		
		for(int y=0; y<type->getNYCell()-1; y++) {
			Cell& cell = getCell(x, y);
			cell.getSurface(SOUTH).setIndex(index++);

			Cell& southCell = getCell(x, y+1);
			southCell.getSurface(NORTH).setIndex(index);

			cell.setNeighbor(SOUTH, southCell);
			southCell.setNeighbor(NORTH, cell);
			
			cell.getSurface(SOUTH).setAdjoint(southCell.getSurface(NORTH));
			southCell.getSurface(NORTH).setAdjoint(cell.getSurface(SOUTH));
			
		}
		
		Cell& rightmost = getCell(x, type->getNYCell()-1);
		rightmost.getSurface(SOUTH).setBoundary(true);
		rightmost.getSurface(SOUTH).setIndex(index++);
	}
	
	
	for(int y=0; y<type->getNYCell(); y++) {
		Cell& leftmost = getCell(0, y);
		CellSurface* north = &leftmost.getSurface(NORTH);
		CellSurface* south = &leftmost.getSurface(SOUTH);
		
		north->setNeighbor(LEFT, *north);
		south->setNeighbor(LEFT, *south);
		
		for(int x=1; x<type->getNXCell(); x++) {
			Cell& eastCell = getCell(x, y);
			CellSurface* nextNorth = &eastCell.getSurface(NORTH);
			CellSurface* nextSouth = &eastCell.getSurface(SOUTH);
			north->setNeighbor(RIGHT, *nextNorth);
			nextNorth->setNeighbor(LEFT, *north);
			south->setNeighbor(RIGHT, *nextSouth);
			nextSouth->setNeighbor(LEFT, *south);
			
			north = nextNorth;
			south = nextSouth;
		}
		
		north->setNeighbor(RIGHT, *north);
		south->setNeighbor(RIGHT, *south);
		
	}
	
	
	for(int x=0; x<type->getNXCell(); x++) {
		Cell& leftmost = getCell(x, 0);
		CellSurface* west = &leftmost.getSurface(WEST);
		CellSurface* east = &leftmost.getSurface(EAST);
		
		west->setNeighbor(LEFT, *west);
		east->setNeighbor(LEFT, *east);
		
		for(int y=1; y<type->getNYCell(); y++) {
			Cell& eastCell = getCell(x, y);
			CellSurface* nextWest = &eastCell.getSurface(WEST);
			CellSurface* nextEast = &eastCell.getSurface(EAST);
			west->setNeighbor(RIGHT, *nextWest);
			nextWest->setNeighbor(LEFT, *west);

			east->setNeighbor(RIGHT, *nextEast);
			nextEast->setNeighbor(LEFT, *east);
			
			west = nextWest;
			east = nextEast;
		}

		west->setNeighbor(RIGHT, *west);
		east->setNeighbor(RIGHT, *east);
		
	}
}

void Assembly::calculateIncomingCurrent() {
	for(boost::ptr_map<int,Cell>::iterator i=cells.begin(), e=cells.end(); i != e; i++) {
		i->second->calculateIncomingCurrent();
	}
}

void Assembly::generateShapeFunction() {
	for(boost::ptr_map<int,Cell>::iterator i=cells.begin(), e=cells.end(); i != e; i++) {
		i->second->generateShapeFunction();
	}
}

void Assembly::calculateAverageAngularFlux() {
	for(boost::ptr_map<int,Cell>::iterator i=cells.begin(), e=cells.end(); i != e; i++) {
		i->second->calculateAverageAngularFlux();
	}
}

void Assembly::generateFunctionalAngularFlux() {
	for(boost::ptr_map<int,Cell>::iterator i=cells.begin(), e=cells.end(); i != e; i++) {
		i->second->generateFunctionalAngularFlux();
	}
}
void Assembly::updateCrossSection() {

	for(boost::ptr_map<int,Cell>::iterator i=cells.begin(), e=cells.end(); i != e; i++) {
		i->second->updateCrossSection();
	}
}

void Assembly::solve(int nIteration, double reigv) {

	for(int y=0; y<type->getNYCell(); y++) {
		for(int x=0; x<type->getNXCell(); x++) {
			Cell& cell = getCell(x, y);

			cell.solveInner(nIteration, reigv);

		}
	}
}

void Assembly::addCell(Cell& cell) {
	int key = type->generateKey(cell.getX(), cell.getY());
	cells.insert(key, &cell);
}

Cell& Assembly::getCell(int x, int y) {
	int key = type->generateKey(x, y);
	return cells[key];
}


void Assembly::setNeighbor(int NEWS, Assembly& neighbor) {
	
	switch (NEWS) {
	case WEST:
		for(int y=0; y<type->getNYCell(); y++) {
			Cell& cell = getCell(0, y);
			Cell& west = neighbor.getCell(neighbor.type->getNXCell()-1, y);
			
			cell.setNeighbor(WEST, west);
			west.setNeighbor(EAST, cell);
				
			cell.getSurface(WEST).setAdjoint(west.getSurface(EAST));
			west.getSurface(EAST).setAdjoint(cell.getSurface(WEST));
		}
		break;
	case EAST:
		for(int y=0; y<type->getNYCell(); y++) {
			Cell& cell = getCell(type->getNXCell()-1, y);
			Cell& east = neighbor.getCell(0, y);
			
			cell.setNeighbor(EAST, east);
			east.setNeighbor(WEST, cell);
				
			cell.getSurface(EAST).setAdjoint(east.getSurface(WEST));
			east.getSurface(WEST).setAdjoint(cell.getSurface(EAST));
		}
		break;
	
	case NORTH:
		for(int x=0; x<type->getNXCell(); x++) {
			Cell& cell 	= getCell(x, 0);
			Cell& north = neighbor.getCell(x, neighbor.type->getNYCell()-1);

			cell.setNeighbor(NORTH, north);
			north.setNeighbor(SOUTH, cell);
			
			cell.getSurface(NORTH).setAdjoint(north.getSurface(SOUTH));
			north.getSurface(SOUTH).setAdjoint(cell.getSurface(NORTH));
		}
		break;
	case SOUTH:
		for(int x=0; x<type->getNXCell(); x++) {
			Cell& cell 	= getCell(x, type->getNYCell()-1);
			Cell& south = neighbor.getCell(x, 0);

			cell.setNeighbor(SOUTH, south);
			south.setNeighbor(NORTH, cell);
			
			cell.getSurface(SOUTH).setAdjoint(south.getSurface(NORTH));
			south.getSurface(NORTH).setAdjoint(cell.getSurface(SOUTH));
		}
		break;
	default:
		break;
	}
	
}

double Assembly::calculateFissionSource() {

	double fissionSource = 0.0;

	for(int y=0; y<type->getNYCell(); y++) {
		for(int x=0; x<type->getNXCell(); x++) {
			Cell& cell = getCell(x, y);

			fissionSource += cell.calculateFissionSource();
		}
	}

	return fissionSource;

}

void Assembly::showResult() {
	for(int y=0; y<type->getNYCell(); y++) {
		for(int x=0; x<type->getNXCell(); x++) {
			Cell& cell = getCell(x, y);
			cell.showResult();
		}
	}
}