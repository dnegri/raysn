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
	int    nPointX;
	int    nPointY;

	double angle;
	double vsine;
	double vcosine;
	double vtangent;
	double rayspace;
	double weight;

	boost::ptr_vector<SurfaceRayPoint> surfacePoints;

public:
	AzimuthalAngle();
	virtual ~AzimuthalAngle();


	double getRayspace() const;
	void setRayspace(double rayspace);

	boost::ptr_vector<SurfaceRayPoint>& getSurfacePoints() ;
	void addSurfaceRayPoint(SurfaceRayPoint& point);
	SurfaceRayPoint& findSurfaceRayPoints(const Point & point, const double width, const int surface);

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
};



#endif /* AZIMUTHALANGLE_H_ */
