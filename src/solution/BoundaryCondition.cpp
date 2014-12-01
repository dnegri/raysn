//
//  BoundaryCondition.cpp
//  raysn
//
//  Created by Jooil Yoon on 11/21/14.
//  Copyright (c) 2014 Jooil Yoon. All rights reserved.
//

#include "BoundaryCondition.h"

BoundaryCondition::BoundaryCondition() {}
BoundaryCondition::~BoundaryCondition() {}

void BoundaryCondition::setBoundary(int inews, int boundaryType) {

	switch(boundaryType) {
	case BOUNDARY_REFLECTIVE:
		boundaryFactor[inews] = 1.0;
		break;
	case BOUNDARY_VACUUM:
		boundaryFactor[inews] = 0.0;
		break;
	default:
		throw std::runtime_error("INVALID BOUNDARY CONDITION VALUE");
		break;
	}
}

double BoundaryCondition::getBoundaryFactor(int inews) {
	return boundaryFactor[inews];
}