//
//  Core.h
//  raysn
//
//  Created by Jooil Yoon on 10/24/14.
//  Copyright (c) 2014 Jooil Yoon. All rights reserved.
//

#ifndef SOLUTION_CORE_H_
#define SOLUTION_CORE_H_

#include "../pch.h"
#include "Assembly.h"

class Core  : public RaysnClass {
private:
	int nxa, nya;
	std::vector<int> rowa;
	boost::ptr_map<int, Assembly> assemblies;

private:
	int generateKey(int x, int y);

public:
	Core(int nxa, int nya, std::vector<int>& rowa);
	virtual ~Core();
	
	void construct(boost::ptr_vector<CellType>& cellTypes, XSLibrary& xsl);
	void updateCrossSection();
	void solve();
	
	
	void addAssembly(Assembly& assembly);
	Assembly& getAssembly(int x, int y);
	
	
	
};

#endif
