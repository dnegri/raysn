//
//  AssemblyType.cpp
//  raysn
//
//  Created by Jooil Yoon on 11/20/14.
//  Copyright (c) 2014 Jooil Yoon. All rights reserved.
//

#include "AssemblyType.h"


AssemblyType::AssemblyType(int nxc, int nyc) : nxc(nxc), nyc(nyc) {
}

AssemblyType::~AssemblyType(){}


int AssemblyType::generateKey(int x, int y) const {
	return x*1000+y;
}

void AssemblyType::defineCellType(int x, int y, const std::string cellTypeName) {
	int key = generateKey(x, y);
	cellNames[key] = cellTypeName;
}


const std::string& AssemblyType::getCellName(int x, int y) const {
	return cellNames.at(generateKey(x, y));
}
