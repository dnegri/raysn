/*
 * pch.h
 *
 *  Created on: Oct 15, 2014
 *      Author: jiyoon
 */

#ifndef PCH_H_
#define PCH_H_

#define LOG4CPP_FIX_ERROR_COLLISION

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include "boost/multi_array.hpp"

#include <array>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <iostream>

#include "log4cpp/Category.hh"

static const int	PLUS  = 1;
static const int	MINUS = -1;

static const int	DIRX  = 0;
static const int	DIRY  = 1;
static const int	DIRXY = 2;

static const int	LEFT	  = 0;
static const int	RIGHT	  = 1;
static const int	LEFTRIGHT = 2;

static const int	FORWARD	 = 0;
static const int	BACKWARD = 1;
static const int	NFORBACK = 2;

static const int 	POSITIVE = 0;
static const int	NEGATIVE = 1;
static const int 	NSLOPE	 = 2;

static const int	SELF  		= 0;
static const int	NEIB  		= 1;
static const int	SELFNEIB  	= 2;


static const int	NW = 0;
static const int	NE = 1;
static const int	SE = 2;
static const int	SW = 3;

static const int	WEST  = 0;
static const int	EAST  = 1;
static const int	NORTH = 2;
static const int	SOUTH = 3;

static const int	NEWS = 4;

static const int	NDIVREG = 8;
static const double RDIVREG = 1.0 / NDIVREG;

static const double PI	= 3.141592;
static const double BIG = 1.E+30;

static const double MICRO = 1.E-6;
static const double MILLI = 1.E-3;

#endif /* PCH_H_ */
