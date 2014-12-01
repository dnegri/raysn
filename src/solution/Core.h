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
#include "../geometry/AssemblyType.h"
#include "Assembly.h"

class Core  : public RaysnClass {
private:

	double eigv 	= 1.0;
	double reigv	= 1.0;
	
	int nOuterIteration = 1000;
	int nInnerIteration = 2;

	int nxa, nya;
	std::vector<std::vector<std::string>>& map;
	boost::ptr_map<int, Assembly> assemblies;

private:
	int generateKey(int x, int y);

public:
	Core(int nxa, int nya, std::vector<std::vector<std::string>>& map);
	virtual ~Core();
	
	void construct(	const boost::ptr_map<const std::string, AssemblyType>& assemblyTypes,
					const boost::ptr_map<const std::string, CellType>& cellTypes,
					const XSLibrary& xsl);
	void calculateIncomingCurrent();
	void generateShapeFunction();
	void calculateAverageAngularFlux();
	void generateFunctionalAngularFlux();
	void updateCrossSection();
	double calculateFissionSource();
	void solve();
	
	
	void addAssembly(Assembly& assembly);
	Assembly& getAssembly(int x, int y);
	
	
	
};

#endif
