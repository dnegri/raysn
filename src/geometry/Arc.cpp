/*
 * Arc.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jiyoon
 */
#include <math.h>
#include "Arc.h"

using namespace std;



Arc::Arc() {
}

Arc::~Arc() {
}

double Arc::getAngle(const Point& point) const{

	Point delta = point - getCenter();

	return atan2(delta.getY(), delta.getX());
}

bool Arc::cross(const Point& point, double slope, int dirX, int dirY,
		Point cross, double length) const {

	// two intersection points
	double yint = point.getY() - slope * point.getX();

	double a0 = 1.0 + pow(slope, 2);
	double b0 = slope * (yint - center->getY()) - center->getX();
	double c0 = pow(center->getX(), 2) + pow(yint - center->getY(), 2)
			- pow(radius, 2);
	double d0 = pow(b0, 2) - a0 * c0;

	if (d0 < 0.0)
		return false;

	Point sol[2];

	sol[0].setX((-b0 + sqrt(d0)) / a0);
	sol[0].setY(slope * sol[0].getX() + yint);

	sol[1].setX((-b0 - sqrt(d0)) / a0);
	sol[1].setY(slope * sol[1].getX() + yint);

	// check the intersection points are on this arc
	double ang1 = getAngle(*beginPoint);
	double ang2 = getAngle(*endPoint);

	if (fabs(ang1 - PI) < MICRO) {
		ang1 = copysign(ang1, ang2);
	}

	if (fabs(ang2 - PI) < MICRO) {
		ang2 = copysign(ang2, ang1);
	}

	bool crossed = false;
	length = BIG;
	double length2 = 0.0;

	for(int i=0; i<2; i++) {
		double ang = getAngle(sol[i]);

		if( (ang1 - ang)*(ang2 - ang) < 0.0 ) {
			Point dxy = sol[i] - point;
	    	crossed =  copysign(dxy.getX(), (double)dirX) == dxy.getX() &&
	    			copysign(dxy.getY(), (double)dirY) == dxy.getY();

		    if(!crossed) continue;

		    length2 = dxy.norm();

		    if(length2 > MICRO && length2 < length) {
		    	length = length2;
		    	cross  =sol[i];
		    }
		}
	}

	crossed = true;

	if(length == BIG) {
		crossed = false;
		length = 0.0;
	}
	return crossed;
}


