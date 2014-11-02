/*
 * CellSurfaceType.h
 *
 *  Created on: Oct 13, 2014
 *      Author: jiyoon
 */

#ifndef CELLTYPESURFACE_H_
#define CELLTYPESURFACE_H_

#include "../pch.h"
#include "Line.h"
#include "SurfaceRayPoint.h"
#include "AzimuthalAngle.h"

class CellTypeSurface : public Line {

public:
	struct Direction {
		int x;
		int y;
	};

private:
	int inews;
	double length;

	boost::ptr_vector<boost::ptr_vector<SurfaceRayPoint>>	surfacePoints;
	std::vector<int>										nPoints;
	std::vector<double>										delta;

	Direction dir[NSLOPE];

public:
	CellTypeSurface();
	CellTypeSurface(int nAngles, int inews, double length);
	virtual ~CellTypeSurface();

	boost::ptr_vector<SurfaceRayPoint>& getPoints(AzimuthalAngle& angle);
	void								addPoint(AzimuthalAngle& angle, SurfaceRayPoint& point);
	SurfaceRayPoint&					findPoint(AzimuthalAngle& angle, double point);
	
	Direction& getDirection(int islope) {
		return dir[islope];
	}
	
	int getNEWS() {
		return inews;
	}
	
};



#endif /* CELLTYPESURFACE_H_ */
