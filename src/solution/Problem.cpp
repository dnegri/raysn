//
//  Problem.cpp
//  raysn
//
//  Created by Jooil Yoon on 10/24/14.
//  Copyright (c) 2014 Jooil Yoon. All rights reserved.
//

#include "Problem.h"
#include "FuelCellType.h"
#include "../xs/C5G7Library.h"

Problem::Problem() {
}

Problem::~Problem() {
	if(core != NULL) delete core;
	
}


void Problem::initialize() {

	xsl = new C5G7Library();
	xsl->initialize();
	
	double			 width	= 1.26;
	int				 nRings = 1;

	std::vector<int> nSubRings;
	nSubRings.push_back(1);

	std::vector<double> radiuses;
	radiuses.push_back(0.54);


	RayInfo rayInfo(4, 0.02);
	
	std::vector<std::string> uo2XSNames;
	std::vector<std::string> moxXSNames;
	
	uo2XSNames.push_back("MOD");
	uo2XSNames.push_back("UO2");

	moxXSNames.push_back("MOD");
	moxXSNames.push_back("MOX87");
	moxXSNames.push_back("MOX70");
	moxXSNames.push_back("MOX43");
	
	FuelCellType* uo2CellType = new FuelCellType(width, nRings, nSubRings, radiuses, uo2XSNames);
	FuelCellType* moxCellType = new FuelCellType(width, nRings, nSubRings, radiuses, moxXSNames);
	
	uo2CellType->construct(rayInfo);
	moxCellType->construct(rayInfo);

	this->cellTypes.insert("UO2",uo2CellType);
	this->cellTypes.insert("MOX",moxCellType);
	
	

//	gnuplotio::Gnuplot gp;
//
//	gp << "set size square\n";
//	gp << "set xrange [0:"<<width<<"]\n";
//	gp << "set yrange [0:"<<width<<"]\n";
//	gp << "plot '-' pt 7 ps 1 lc rgb 'blue' \n";
//
//	gp.send1d(fct->plotData);
	
	std::vector<int> rowa;
	
	rowa.push_back(1);
	
//	core = new Core(1,1, rowa);
//	
//	core->construct(cellTypes, *xsl);
}





void Problem::solve() {
	core->updateCrossSection();
	core->solve();
}