/*
 * Arc.h
 *
 *  Created on: Oct 10, 2014
 *      Author: jiyoon
 */

#ifndef ARC_H_
#define ARC_H_

#include "../pch.h"
#include "Point.h"
#include "Line.h"



class Arc : public Line {
protected:
	Point* center;
	double radius;

public:
	Arc();
	virtual ~Arc();

	double getAngle(const Point& point) const;

	void setCenter(Point& center) {
		this->center = &center;
	}

	const Point& getCenter() const {
		return *center;
	}

	double getRadius() const {
		return radius;
	}

	void setRadius(double radius) {
		this->radius = radius;
	}

	virtual bool cross(const Point& point, double& slope, int& dirX, int& dirY, Point& cross, double& length) const;

};



#endif /* ARC_H_ */
