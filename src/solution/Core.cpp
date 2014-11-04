//
//  Core.cpp
//  raysn
//
//  Created by Jooil Yoon on 10/24/14.
//  Copyright (c) 2014 Jooil Yoon. All rights reserved.
//

#include "Core.h"


Core::Core(int nxa, int nya, std::vector<int>& rowa) : nxa(nxa), nya(nya), rowa(rowa) {

	
}

Core::~Core() {
}


void Core::construct(boost::ptr_vector<CellType>& cellTypes, XSLibrary& xsl) {
	Assembly* assembly = new Assembly(0,0,2,2);
	assembly->construct(cellTypes, xsl);
	this->addAssembly(*assembly);
	
	
	
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

void Core::solve() {
	
	for(int y=0; y<nya; ++y) {
	for(int x=0; x<nxa; ++x) {
		Assembly& assembly = getAssembly(x, y);
		assembly.solve();
	}
	}
}

void Core::updateCrossSection() {
	for(boost::ptr_map<int, Assembly>::iterator i=assemblies.begin(), e=assemblies.end(); i!=e; ++i) {
		i->second->updateCrossSection();
	}
}
