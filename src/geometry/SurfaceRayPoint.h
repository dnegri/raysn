/*
 * SurfacePoint.h
 *
 *  Created on: Oct 15, 2014
 *      Author: jiyoon
 */

#ifndef SURFACERAYPOINT_H_
#define SURFACERAYPOINT_H_

#include "../pch.h"
#include "SurfaceRay.h"
#include "Point.h"

static const int POSITIVE  = 0;
static const int NEGATIVE  = 1;
static const int NSLOPE    = 2;


class SurfaceRayPoint : public Point {

private:
	int   inews;
	Line* cellSurface;
	Line* subRegionSurface;
	SurfaceRayPoint* endPoints[NSLOPE];
	SubRegionType* subRegion;
	SurfaceRay ray[NSLOPE];

	struct Direction {
		int x;
		int y;
	};
	Direction dir[NSLOPE];


public:
	SurfaceRayPoint();
	virtual ~SurfaceRayPoint();

	SurfaceRay& getRay(int islope) {
		return ray[islope];
	}

	Line& getSurface() {
		return *cellSurface;
	}

	Direction& getDirection(int islope) {
		return dir[islope];
	}

	void setCellSurface(Line& surface, int inews);

	void setEndPoint(int islope, SurfaceRayPoint& point);

	SurfaceRayPoint& getEndPoint(int islope) {
		return *endPoints[islope];
	}

	int getNEWS() {
		return inews;
	}

	const Line& getSubRegionSurface() const {
		return *subRegionSurface;
	}

	void setSubRegionSurface(Line& subRegionSurface) {
		this->subRegionSurface = &subRegionSurface;
	}

	SubRegionType& getSubRegion() const {
		return *subRegion;
	}

	void setSubRegion(SubRegionType& subRegion) {
		this->subRegion = &subRegion;
	}
};



#endif /* SURFACEPOINT_H_ */
