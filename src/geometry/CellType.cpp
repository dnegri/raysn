/*
 * CellType.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jiyoon
 */

#include "CellType.h"



CellType::CellType(double xsize, double ysize) : xsize(xsize), ysize(ysize), logger(log4cpp::Category::getInstance("CellType")){
}

CellType::~CellType() {
	// TODO Auto-generated destructor stub
}


