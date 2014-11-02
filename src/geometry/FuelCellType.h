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

	int								  nCircles;

	double							  hwidth;
	double							  rwidth;
	double							  rvolume;

public:
	std::vector<boost::tuple<double, double> > plotData;

public:
	FuelCellType(const double width, const int nRings, const std::vector<int>& nSubRings, const std::vector<double>& radiuses);
	virtual ~FuelCellType();

	void construct(RayInfo& ri);
	void fixSegment();
	
	void initRegions();
	void initPoints();
	void initLines();
	void initSurfaceRays();
	void initSegments(SurfaceRayPoint& point, int islope, double slope);

	double getRadius(int iCircle);


	double getWidth() const {
		return width;
	}
};



#endif /* FUELCELLTYPE_H_ */
