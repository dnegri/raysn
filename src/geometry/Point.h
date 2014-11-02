/*
 * Point.h
 *
 *  Created on: Oct 10, 2014
 *      Author: jiyoon
 */

#ifndef POINT_H_
#define POINT_H_

#include "../pch.h"



class Point {
private:
	double x, y;

public:
	Point();
	Point(double x, double y);
	virtual ~Point();

	double getValue(int direction);

	virtual bool operator==(const Point& p2) {
		bool equal = fabs(this->x - p2.x) < MICRO && fabs(this->y - p2.y) < MICRO;
		return equal;
	}

	Point& operator+=(const Point& p2) {
		this->x += p2.x;
		this->y += p2.y;

		return *this;
	}

	Point& operator-=(const Point& p2) {
		this->x -= p2.x;
		this->y -= p2.y;

		return *this;
	}

	double getX() const {
		return x;
	}

	void setX(double x) {
		this->x = x;
	}

	double getY() const {
		return y;
	}

	void setY(double y) {
		this->y = y;
	}

	double norm() const;
};

inline Point operator+(Point p1, const Point& p2) {
	p1 += p2;
	return p1;
}

inline Point operator-(Point p1, const Point& p2) {
	p1 -= p2;
	return p1;
}



#endif /* POINT_H_ */
