//
//  Core.cpp
//  raysn
//
//  Created by Jooil Yoon on 10/24/14.
//  Copyright (c) 2014 Jooil Yoon. All rights reserved.
//

#include "Core.h"


Core::Core(int nxa, int nya, std::vector<std::vector<std::string>>& map) : nxa(nxa), nya(nya), map(map) {
	
}

Core::~Core() {
}


void Core::construct(	const boost::ptr_map<const std::string, AssemblyType>& assemblyTypes,
						const boost::ptr_map<const std::string, CellType>& cellTypes,
						const XSLibrary& xsl) {
	
	
	for(int j=0; j<nya; j++) {
		for(int i=0; i<nxa; i++) {
			std::string assemblyName = map.at(j).at(i);
			Assembly* assembly = new Assembly(i,j, assemblyTypes.at(assemblyName));
			assembly->construct(cellTypes, xsl);
			addAssembly(*assembly);
		}
	}

	for(int y=0; y<nya; y++) {
		for(int x=0; x<nxa-1; x++) {
			Assembly& self = getAssembly(x, y);
			Assembly& east = getAssembly(x+1, y);

			self.setNeighbor(EAST, east);
			east.setNeighbor(WEST, self);
		}
	}
	
	for(int x=0; x<nxa; x++) {
		for(int y=0; y<nya-1; y++) {
			Assembly& self = getAssembly(x, y);
			Assembly& south = getAssembly(x, y+1);

			self.setNeighbor(SOUTH, south);
			south.setNeighbor(NORTH, self);
		}
		
	}
}

void Core::addAssembly(Assembly& assembly) {

	int key = generateKey(assembly.getX(), assembly.getY());
	assemblies.insert(key, &assembly);
}

Assembly& Core::getAssembly(int x, int y) {
	int key = generateKey(x, y);
	return assemblies[key];
}

int Core::generateKey(int x, int y) {
	return x*1000+y;
}

double Core::calculateFissionSource() {
	double fissionSource = 0.0;
	for(int y=0; y<nya; ++y) {
	for(int x=0; x<nxa; ++x) {
		Assembly& assembly = getAssembly(x, y);
		fissionSource+=assembly.calculateFissionSource();
	}
	}
	
	return fissionSource;
}

void Core::generateFunctionalAngularFlux() {
	for(int y=0; y<nya; ++y) {
	for(int x=0; x<nxa; ++x) {
		Assembly& assembly = getAssembly(x, y);
		assembly.generateFunctionalAngularFlux();
	}
	}
	
}

void Core::calculateIncomingCurrent() {
	for(int y=0; y<nya; ++y) {
	for(int x=0; x<nxa; ++x) {
		Assembly& assembly = getAssembly(x, y);
		assembly.calculateIncomingCurrent();
	}
	}
	
}

void Core::generateShapeFunction() {
	for(int y=0; y<nya; ++y) {
	for(int x=0; x<nxa; ++x) {
		Assembly& assembly = getAssembly(x, y);
		assembly.generateShapeFunction();
	}
	}
	
}

void Core::calculateAverageAngularFlux() {
	for(int y=0; y<nya; ++y) {
	for(int x=0; x<nxa; ++x) {
		Assembly& assembly = getAssembly(x, y);
		assembly.calculateAverageAngularFlux();
	}
	}
	
}


void Core::solve() {

	double fissionSource = calculateFissionSource();

	
	for(int iout=0; iout < nOuterIteration; iout++) {

//		generateFunctionalAngularFlux();
		calculateIncomingCurrent();
		generateShapeFunction();
		calculateAverageAngularFlux();
		
		for(int y=0; y<nya; ++y) {
		for(int x=0; x<nxa; ++x) {
			Assembly& assembly = getAssembly(x, y);
			assembly.solve(nInnerIteration, reigv);
		}
		}
		
		double newFissionSource = calculateFissionSource();
		
		double newEigv = eigv*newFissionSource/fissionSource;
		logger.info("K-EFF: %12.6f", newEigv);
		
		if(fabs(eigv-newEigv) < MICRO*1.E-1) {
			logger.info("CALCULATION WAS FINISHED SUCCESSFULLY");
			break;
		}

		eigv		  = newEigv;
		reigv		  = 1./eigv;
		fissionSource = newFissionSource;
	}
}

void Core::updateCrossSection() {
	for(boost::ptr_map<int, Assembly>::iterator i=assemblies.begin(), e=assemblies.end(); i!=e; ++i) {
		i->second->updateCrossSection();
	}
}
