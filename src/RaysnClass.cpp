//
//  RaysnClass.cpp
//  raysn
//
//  Created by Jooil Yoon on 11/3/14.
//  Copyright (c) 2014 Jooil Yoon. All rights reserved.
//
#include <typeinfo>
#include "RaysnClass.h"


RaysnClass::RaysnClass() : logger(log4cpp::Category::getInstance(typeid(*this).name())){

}

RaysnClass::~RaysnClass() {}
