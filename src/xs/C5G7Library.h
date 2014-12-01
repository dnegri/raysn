//
//  C5G7Libary.h
//  raysn
//
//  Created by Jooil Yoon on 11/17/14.
//  Copyright (c) 2014 Jooil Yoon. All rights reserved.
//

#ifndef __raysn__C5G7Library__
#define __raysn__C5G7Library__

#include "../pch.h"
#include "XSLibrary.h"

class C5G7Library : public XSLibrary {

public:
	C5G7Library();
	virtual ~C5G7Library();
	
	virtual void initialize();
	
	CrossSection* getUO2XS();
	CrossSection* getMOX87();
	CrossSection* getMOX70();
	CrossSection* getMOX43();
	CrossSection* getModeratorXS();
	CrossSection* getGuideTubeXS();
};

#endif /* defined(__raysn__C5G7Libary__) */
