/*
 * Assembly.h
 *
 *  Created on: Oct 17, 2014
 *      Author: jiyoon
 */

#ifndef SOLUTION_ASSEMBLY_H_
#define SOLUTION_ASSEMBLY_H_
#include "../pch.h"
#include "Cell.h"

class Assembly {
private:
	boost::ptr_vector<Cell> cells;
public:
	Assembly();
	virtual ~Assembly();
};

#endif /* SOLUTION_ASSEMBLY_H_ */
