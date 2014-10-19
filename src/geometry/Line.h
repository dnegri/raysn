/*
 * Line.h
 *
 *  Created on: Oct 10, 2014
 *      Author: jiyoon
 */

#ifndef LINE_H_
#define LINE_H_

#include "../pch.h"
#include "Shape.h"
#include "Point.h"


class SubRegionType;

class Line : public Shape {
protected:
	Point* beginPoint;
	Point* endPoint;
	SubRegionType* subRegions[2];

public:
	Line();
	virtual ~Line();

	const Point& getBeginPoint() {
		return *beginPoint;
	}

	const Point& getEndPoint() {
		return *endPoint;
	}

	void setBeginPoint(Point& beginPoint);
	void setEndPoint(Point& endPoint);

	virtual bool cross(const Point& point, double& slope, int& dirX, int& dirY, Point& cross, double& length) const;

	void addSubRegion(SubRegionType& subRegion);

	SubRegionType& getNeighborSubRegion(SubRegionType& subRegion);
};



#endif /* LINE_H_ */
