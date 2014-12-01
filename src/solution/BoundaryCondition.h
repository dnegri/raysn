//
//  BoundaryCondition.h
//  raysn
//
//  Created by Jooil Yoon on 11/21/14.
//  Copyright (c) 2014 Jooil Yoon. All rights reserved.
//

#ifndef __raysn__BoundaryCondition__
#define __raysn__BoundaryCondition__

#include "../pch.h"

class BoundaryCondition  : public RaysnClass {

public:
	static const int BOUNDARY_REFLECTIVE 	= 0;
	static const int BOUNDARY_VACUUM 		= 1;

private:
	double boundaryFactor[NEWS];
	
private:
	BoundaryCondition();
public:
	static BoundaryCondition& getInstance() {
		static BoundaryCondition instance;
		return instance;
	}
	virtual ~BoundaryCondition();

	void setBoundary(int inews, int boundaryType);
	
	double getBoundaryFactor(int inews);

};


#endif /* defined(__raysn__BoundaryCondition__) */
