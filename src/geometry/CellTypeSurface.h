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

	const boost::ptr_vector<SurfaceRayPoint>& 	getPoints(const AzimuthalAngle& angle) const ;
	boost::ptr_vector<SurfaceRayPoint>& 		getPoints(const AzimuthalAngle& angle);
	void										addPoint(const AzimuthalAngle& angle, SurfaceRayPoint& point);
	const SurfaceRayPoint&						findPoint(const AzimuthalAngle& angle, double point) const;


	int getNumberOfAngles() const ;
	int getNumberOfPoints(AzimuthalAngle& angle) const;
	int getNumberOfPoints(int indexOfAngle) const;
	
	const Direction& getDirection(int islope) const {
		return dir[islope];
	}
	
	Direction& getDirection(int islope) {
		return dir[islope];
	}
	
	int getNEWS() const {
		return inews;
	}
	
	double getLength() const {
		return length;
	}
	
};



#endif /* CELLTYPESURFACE_H_ */
