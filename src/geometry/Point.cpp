/*
 * Point.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jiyoon
 */

#include "Point.h"



Point::Point() {
	x = 0;
	y = 0;
}

Point::Point(double x, double y) : x(x), y(y) {

}

Point::~Point() {

}

double Point::norm() const {
	return sqrt(pow(x,2.0) + pow(y,2.0));
}

double Point::getValue(int inews) {
	
	double value = 0.0;
	
	switch(inews) {
	case NORTH:
	case SOUTH:
		value = this->getX();
		break;
	case WEST:
	case EAST:
		value = this->getY();
		break;
	}
	
	return value;
}



