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

class CellType : public RaysnClass {
	
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

	const boost::ptr_vector<AzimuthalAngle>& getAngles() const {
		return angles;
	}

	const boost::ptr_vector<RegionType>& getRegions() const {
		return regions;
	}

	double getVolume() const {
		return volume;
	}

	void setVolume(double volume) {
		this->volume = volume;
	}
	
	const CellTypeSurface& getSurface(int inews) const {
		return surfaces.at(inews);
	}
	
	double getXSize() const {
		return xsize;
	}
	
	double getYSize() const {
		return ysize;
	}
	
};



#endif /* CELLTYPE_H_ */
