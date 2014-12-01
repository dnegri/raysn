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

class CellTypeSurface;

class SurfaceRayPoint : public Point {

private:
	int				 index;
	Line*			 subRegionSurface;
	SubRegionType*	 subRegion;
	SurfaceRay		 ray[NSLOPE];
	CellTypeSurface* surface;


public:
	SurfaceRayPoint(CellTypeSurface& surface);
	virtual ~SurfaceRayPoint();
	
	const SurfaceRay& getRay(int islope) const {
		return ray[islope];
	}
	
	SurfaceRay& getRay(int islope) {
		return ray[islope];
	}


	const CellTypeSurface& getSurface() const {
		return *surface;
	}
	
	CellTypeSurface& getSurface() {
		return *surface;
	}
	
	const Line& getSubRegionSurface() const {
		return *subRegionSurface;
	}

	void setSubRegionSurface(Line& subRegionSurface) {
		this->subRegionSurface = &subRegionSurface;
	}

	const SubRegionType& getSubRegion() const {
		return *subRegion;
	}
	
	SubRegionType& getSubRegion() {
		return *subRegion;
	}

	void setSubRegion(SubRegionType& subRegion) {
		this->subRegion = &subRegion;
	}
	
	int getIndex() const {
		return index;
	}
	
	void setIndex(int index) {
		this->index = index;
	}
};



#endif /* SURFACEPOINT_H_ */
