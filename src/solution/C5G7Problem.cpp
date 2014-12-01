//
//  C5G7Problem.cpp
//  raysn
//
//  Created by Jooil Yoon on 11/20/14.
//  Copyright (c) 2014 Jooil Yoon. All rights reserved.
//

#include "C5G7Problem.h"
#include "C5G7Library.h"
#include "FuelCellType.h"
#include "BoundaryCondition.h"

C5G7Problem::C5G7Problem() {}
C5G7Problem::~C5G7Problem() {}


void C5G7Problem::initialize() {

	xsl = new C5G7Library();
	xsl->initialize();
	
	
	BoundaryCondition& bc = BoundaryCondition::getInstance();
	bc.setBoundary(NORTH, 	BoundaryCondition::BOUNDARY_REFLECTIVE);
	bc.setBoundary(WEST, 	BoundaryCondition::BOUNDARY_REFLECTIVE);
	bc.setBoundary(SOUTH, 	BoundaryCondition::BOUNDARY_REFLECTIVE);
	bc.setBoundary(EAST, 	BoundaryCondition::BOUNDARY_REFLECTIVE);
	
	double			 width	= 1.26;
	int				 nRings = 1;

	std::vector<int> nSubRings;
	nSubRings.push_back(1);

	std::vector<double> radiuses;
	radiuses.push_back(0.54);


	RayInfo rayInfo(16, 0.01);
	
	std::vector<std::string> uo2XSNames;
	std::vector<std::string> mox87XSNames;
	std::vector<std::string> mox70XSNames;
	std::vector<std::string> mox43XSNames;
	std::vector<std::string> gtXSNames;
	std::vector<std::string> modXSNames;
	
	uo2XSNames.push_back("MOD");
	uo2XSNames.push_back("UO2");

	mox87XSNames.push_back("MOD");
	mox87XSNames.push_back("MOX87");
	
	mox70XSNames.push_back("MOD");
	mox70XSNames.push_back("MOX70");
	
	mox43XSNames.push_back("MOD");
	mox43XSNames.push_back("MOX43");

	gtXSNames.push_back("MOD");
	gtXSNames.push_back("GT");
	
	modXSNames.push_back("MOD");
	modXSNames.push_back("MOD");
	
	FuelCellType* uo2CellType 	= new FuelCellType(width, nRings, nSubRings, radiuses, uo2XSNames);
	FuelCellType* mox87CellType = new FuelCellType(width, nRings, nSubRings, radiuses, mox87XSNames);
	FuelCellType* mox70CellType = new FuelCellType(width, nRings, nSubRings, radiuses, mox70XSNames);
	FuelCellType* mox43CellType = new FuelCellType(width, nRings, nSubRings, radiuses, mox43XSNames);
	FuelCellType* gtCellType 	= new FuelCellType(width, nRings, nSubRings, radiuses, gtXSNames);
	FuelCellType* modCellType 	= new FuelCellType(width, nRings, nSubRings, radiuses, modXSNames);
	
	uo2CellType->construct(rayInfo);
	mox87CellType->construct(rayInfo);
	mox70CellType->construct(rayInfo);
	mox43CellType->construct(rayInfo);
	gtCellType->construct(rayInfo);
	modCellType->construct(rayInfo);

	this->cellTypes.insert("UO2",uo2CellType);
	this->cellTypes.insert("MOX87",mox87CellType);
	this->cellTypes.insert("MOX70",mox70CellType);
	this->cellTypes.insert("MOX43",mox43CellType);
	this->cellTypes.insert("GT",gtCellType);
	this->cellTypes.insert("MOD",modCellType);
	
	this->assemblyTypes.insert("UO2", createUO2AssemblyType());
	this->assemblyTypes.insert("MOX", createMOXAssemblyType());
	this->assemblyTypes.insert("MOD", createMODAssemblyType());
	
	std::vector<std::vector<std::string>> map;
	
//	int nya = 3;
//	int nxa = 3;
//	
//	std::vector<std::string> row1;
//	row1.push_back("UO2");
//	row1.push_back("MOX");
//	row1.push_back("MOD");
//	map.push_back(row1);
//
//	std::vector<std::string> row2;
//	row2.push_back("MOX");
//	row2.push_back("UO2");
//	row2.push_back("MOD");
//	map.push_back(row2);
//	
//	std::vector<std::string> row3;
//	row3.push_back("MOD");
//	row3.push_back("MOD");
//	row3.push_back("MOD");
//	map.push_back(row3);

	int nya = 1;
	int nxa = 1;
	
	std::vector<std::string> row1;
//	row1.push_back("UO2");
	row1.push_back("MOX");
//	row1.push_back("MOD");
	map.push_back(row1);

	core = new Core(nxa, nya, map);
	
	core->construct(assemblyTypes, cellTypes, *xsl);
}

AssemblyType* C5G7Problem::createUO2AssemblyType() {
	int npinx = 17;
	int npiny = 17;

	AssemblyType* a = new AssemblyType(npinx, npiny);
	
	for(int j=0; j<npiny; j++) {
		for(int i=0; i<npinx; i++) {
			a->defineCellType(i, j, "UO2");
		}
	}
	
	a->defineCellType(5,   2, "GT");
	a->defineCellType(8,   2, "GT");
	a->defineCellType(11,  2, "GT");

	a->defineCellType(3,   3, "GT");
	a->defineCellType(13,  3, "GT");

	a->defineCellType(2,   5, "GT");
	a->defineCellType(5,   5, "GT");
	a->defineCellType(8,   5, "GT");
	a->defineCellType(11,  5, "GT");
	a->defineCellType(14,  5, "GT");

	a->defineCellType(2,   8, "GT");
	a->defineCellType(5,   8, "GT");
	a->defineCellType(8,   8, "GT");
	a->defineCellType(11,  8, "GT");
	a->defineCellType(14,  8, "GT");
	
	a->defineCellType(2,  11, "GT");
	a->defineCellType(5,  11, "GT");
	a->defineCellType(8,  11, "GT");
	a->defineCellType(11, 11, "GT");
	a->defineCellType(14, 11, "GT");

	a->defineCellType(3,  13, "GT");
	a->defineCellType(13, 13, "GT");
	
	a->defineCellType(5,  14, "GT");
	a->defineCellType(8,  14, "GT");
	a->defineCellType(11, 14, "GT");

	return a;
	
}

AssemblyType* C5G7Problem::createMOXAssemblyType() {
	int npinx = 1;
	int npiny = 1;

	AssemblyType* a = new AssemblyType(npinx, npiny);
	
	for(int j=0; j<npiny; j++) {
		for(int i=0; i<npinx; i++) {
			a->defineCellType(i, j, "MOX43");
		}
	}
	
	return a;
	
	for(int j=1; j<npiny-1; j++) {
		for(int i=1; i<npinx-1; i++) {
			a->defineCellType(i, j, "MOX70");
		}
	}
	
	for(int j=3; j<npiny-3; j++) {
		for(int i=3; i<npinx-3; i++) {
			a->defineCellType(i, j, "MOX87");
		}
	}
	
	a->defineCellType(4, 3, "MOX70");
	a->defineCellType(12,3, "MOX70");
	a->defineCellType(3, 4, "MOX70");
	a->defineCellType(13,4, "MOX70");
	a->defineCellType(3,12, "MOX70");
	a->defineCellType(13,12,"MOX70");
	a->defineCellType(4,13, "MOX70");
	a->defineCellType(12,13,"MOX70");
	
	
	a->defineCellType(5,   2, "GT");
	a->defineCellType(8,   2, "GT");
	a->defineCellType(11,  2, "GT");

	a->defineCellType(3,   3, "GT");
	a->defineCellType(13,  3, "GT");

	a->defineCellType(2,   5, "GT");
	a->defineCellType(5,   5, "GT");
	a->defineCellType(8,   5, "GT");
	a->defineCellType(11,  5, "GT");
	a->defineCellType(14,  5, "GT");

	a->defineCellType(2,   8, "GT");
	a->defineCellType(5,   8, "GT");
	a->defineCellType(8,   8, "GT");
	a->defineCellType(11,  8, "GT");
	a->defineCellType(14,  8, "GT");
	
	a->defineCellType(2,  11, "GT");
	a->defineCellType(5,  11, "GT");
	a->defineCellType(8,  11, "GT");
	a->defineCellType(11, 11, "GT");
	a->defineCellType(14, 11, "GT");

	a->defineCellType(3,  13, "GT");
	a->defineCellType(13, 13, "GT");
	
	a->defineCellType(5,  14, "GT");
	a->defineCellType(8,  14, "GT");
	a->defineCellType(11, 14, "GT");
	return a;

}

AssemblyType* C5G7Problem::createMODAssemblyType() {
	int npinx = 17;
	int npiny = 17;

	AssemblyType* a = new AssemblyType(npinx, npiny);
	
	for(int j=0; j<npiny; j++) {
		for(int i=0; i<npinx; i++) {
			a->defineCellType(i, j, "MOD");
		}
	}
	
	return a;
}

void C5G7Problem::solve() {
	core->updateCrossSection();
	core->solve();
}