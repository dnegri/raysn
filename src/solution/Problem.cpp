//
//  Problem.cpp
//  raysn
//
//  Created by Jooil Yoon on 10/24/14.
//  Copyright (c) 2014 Jooil Yoon. All rights reserved.
//

#include "Problem.h"
#include "FuelCellType.h"
#include "gnuplot-iostream.h"

Problem::Problem() {
}

Problem::~Problem() {
	if(core != NULL) delete core;
	
}


void Problem::initialize() {
	double			 width	= 1.28776;
	int				 nRings = 1;

	std::vector<int> nSubRings;
	nSubRings.push_back(1);

	std::vector<double> radiuses;
	radiuses.push_back(0.41275);

	xsl.initialize();

	RayInfo rayInfo(4, 8, 0.2);
	
	FuelCellType* fct = new FuelCellType(width, nRings, nSubRings, radiuses);
	
	fct->construct(rayInfo);

	this->cellTypes.push_back(fct);

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
	
	core = new Core(1,1, rowa);
	
	core->construct(cellTypes, xsl);
}

void Problem::solve() {
	core->updateCrossSection();
	core->solve();
}