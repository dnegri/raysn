/*
 * Circle.h
 *
 *  Created on: Oct 11, 2014
 *      Author: jiyoon
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "../pch.h"
#include "Point.h"



class Circle {

private:
	const Point& center;
	const double radius;

public:
	Circle(const Point& center, const double radius);
	virtual ~Circle();
};



#endif /* CIRCLE_H_ */
