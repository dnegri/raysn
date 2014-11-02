/*
 * CellType.h
 *
 *  Created on: Oct 10, 2014
 *      Author: jiyoon
 */

#ifndef CELLTYPE_H_
#define CELLTYPE_H_

#include "../pch.h"
#include "Point.h"
#include "Line.h"
#include "AzimuthalAngle.h"
#include "RegionType.h"
#include "CellTypeSurface.h"
#include "RayInfo.h"

class CellType {

public:
	log4cpp::Category& logger;
	
protected:
	double xsize;
	double ysize;
	
	double							  volume;

	Point							  corner[NEWS];
	boost::ptr_vector<AzimuthalAngle> angles;

	boost::ptr_vector<Point>		  points;
	boost::ptr_vector<Line>			  lines;
	boost::ptr_vector<RegionType>	  regions;

	boost::ptr_vector<CellTypeSurface> surfaces;

public:
	CellType(double xsize, double ysize);
	virtual ~CellType();

	virtual void construct(RayInfo& ri) = 0;
	virtual void fixSegment() = 0;

	boost::ptr_vector<AzimuthalAngle>& getAngles() {
		return angles;
	}

	boost::ptr_vector<RegionType>& getRegions() {
		return regions;
	}

	double getVolume() {
		return volume;
	}

	void setVolume(double volume) {
		this->volume = volume;
	}
	
	CellTypeSurface& getSurface(int inews) {
		return surfaces.at(inews);
	}
	
	double getXSize() {
		return xsize;
	}
	
	double getYSize() {
		return ysize;
	}
	
};



#endif /* CELLTYPE_H_ */
