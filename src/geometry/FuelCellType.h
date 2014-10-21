/*
 * FuelCellType.h
 *
 *  Created on: Oct 11, 2014
 *      Author: jiyoon
 */

#ifndef FUELCELLTYPE_H_
#define FUELCELLTYPE_H_

#include "../pch.h"

#include "CellType.h"
#include "RayInfo.h"
#include "AzimuthalAngle.h"
#include "Point.h"
#include "Line.h"
#include "RegionType.h"
#include "XSLibrary.h"
#include "gnuplot-iostream.h"


class FuelCellType : public CellType {
private:
	int								  nRings;
	double							  width;
	std::vector<int>				  nSubRings;
	std::vector<double>				  radiuses;

	Point							  center;
	Point							  corner[NEWS];
	Line							  surface[NEWS];

	int								  nCircles;

	double							  hwidth;
	double							  rwidth;
	double							  volume;
	double							  rvolume;

	boost::ptr_vector<AzimuthalAngle> angles;

	boost::ptr_vector<Point>		  points;
	boost::ptr_vector<Line>			  lines;
	boost::ptr_vector<RegionType>	  regions;

public:
	std::vector<boost::tuple<double, double> > plotData;

public:
	FuelCellType(const double width, const int nRings, const std::vector<int>& nSubRings, const std::vector<double>& radiuses);
	virtual ~FuelCellType();

	void construct(RayInfo& ri);
	void initRegions();
	void initPoints();
	void initLines();
	void initSurfaceRays();
	void initSegments(SurfaceRayPoint& point, int islope, double slope);

	double getRadius(int iCircle);

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

	double getWidth() const {
		return width;
	}
};



#endif /* FUELCELLTYPE_H_ */
