//
//  Problem.h
//  raysn
//
//  Created by Jooil Yoon on 10/24/14.
//  Copyright (c) 2014 Jooil Yoon. All rights reserved.
//

#ifndef __raysn__Problem__
#define __raysn__Problem__

#include "../pch.h"
#include "../geometry/CellType.h"
#include "../xs/XSLibrary.h"
#include "../geometry/RayInfo.h"
#include "Core.h"

class Problem {
private:
	boost::ptr_vector<CellType> cellTypes;
	RayInfo						rayInfo;
	XSLibrary	 				xsl;
	Core* 						core;
	
	
public:
	Problem();
	virtual ~Problem();
	
	void initialize();
	void solve();
};

#endif /* defined(__raysn__Problem__) */
