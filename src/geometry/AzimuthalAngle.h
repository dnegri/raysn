/*
 * AzimuthalAngle.h
 *
 *  Created on: Oct 10, 2014
 *      Author: jiyoon
 */

#ifndef AZIMUTHALANGLE_H_
#define AZIMUTHALANGLE_H_

#include "../pch.h"
#include "SurfaceRayPoint.h"



class AzimuthalAngle {

private:
	int								   index;
	int								   nPointX;
	int								   nPointY;

	double							   angle;
	double							   vsine;
	double							   vcosine;
	double							   vtangent;
	double							   rayspace;
	double							   weight;

public:
	AzimuthalAngle(int index);
	virtual ~AzimuthalAngle();


	double getRayspace() const;
	void   setRayspace(double rayspace);


	void setAngle(double angle);
	void setWeight(double weight);

	double getAngle() const;
	double getCosine() const;
	double getSine() const;
	double getTangent() const;
	double getWeight() const;

	int getPointX() const {
		return nPointX;
	}

	void setPointX(int pointX) {
		nPointX = pointX;
	}

	int getPointY() const {
		return nPointY;
	}

	void setPointY(int pointY) {
		nPointY = pointY;
	}
	
	int getIndex() {
		return index;
	}
};



#endif /* AZIMUTHALANGLE_H_ */
