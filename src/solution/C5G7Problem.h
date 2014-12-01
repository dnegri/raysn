//
//  C5G7Problem.h
//  raysn
//
//  Created by Jooil Yoon on 11/20/14.
//  Copyright (c) 2014 Jooil Yoon. All rights reserved.
//

#ifndef __raysn__C5G7Problem__
#define __raysn__C5G7Problem__

#include "../pch.h"
#include "Problem.h"

class C5G7Problem  : public Problem {

private:
	AssemblyType* createUO2AssemblyType();
	AssemblyType* createMOXAssemblyType();
	AssemblyType* createMODAssemblyType();

public:
	C5G7Problem();
	virtual ~C5G7Problem();
	
	virtual void initialize();
	virtual void solve();

};

#endif /* defined(__raysn__C5G7Problem__) */
