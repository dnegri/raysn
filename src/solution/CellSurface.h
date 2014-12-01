/*
 * CellSurface.h
 *
 *  Created on: Oct 17, 2014
 *      Author: jiyoon
 */

#ifndef SOLUTION_CELLSURFACE_H_
#define SOLUTION_CELLSURFACE_H_

#include "../pch.h"
#include "../geometry/CellTypeSurface.h"
#include "../geometry/CellType.h"
#include "../xs/XSLibrary.h"

typedef boost::multi_array<std::vector<double>, 4> SurfaceAngularFlux;

class CellSurface  : public RaysnClass {
private:
	static const int SHAPE_ORDER = 3;
	
	int index;
	bool boundary;
	double* incomingCurrent;
	SurfaceAngularFlux* angularFlux;
	SurfaceAngularFlux* functionalAngularFlux;
	
	const XSLibrary* xsl;
	const CellTypeSurface* type;
	
	CellSurface* adjoint;
	CellSurface* neighbor[LEFTRIGHT];
	std::vector<double*> shapeFunction;
	
	boost::multi_array<double, 4>* averageAngularFlux;
	boost::multi_array<std::vector<double>*, 2>* funtionalCurrents;
	

public:
	CellSurface();
	CellSurface(const CellTypeSurface& type, const XSLibrary& xsl, bool boundary=false);
	virtual ~CellSurface();

	double getAngFluxFromFAF(int igroup, const AzimuthalAngle& angle, const SurfaceRayPoint& point, int slope, int ipolar);
	double getAngFluxFromShapeFunction(int igroup, const AzimuthalAngle& angle, const SurfaceRayPoint& point, int slope, int ipolar);
	double getAngFlux(int igroup, const AzimuthalAngle& angle, const SurfaceRayPoint& point, int slope, int ipolar);
	void setAngFlux(int igroup, const AzimuthalAngle& angle, const SurfaceRayPoint& point, int slope, int ipolar, double angFlux);
	
	void calculateAverageAngularFlux(const boost::ptr_vector<AzimuthalAngle>& angles);
	const double* calculateIncomingCurrent(const boost::ptr_vector<AzimuthalAngle>& angles);
	void generateFunctionalCurrent(const boost::ptr_vector<AzimuthalAngle>& angles);
	void generateShapeFunction();
	void generateFunctionalAngularFlux(const boost::ptr_vector<AzimuthalAngle>& angles);
	void fitLeastSquare(const std::vector<double>& positions, const std::vector<double>& values, std::vector<double>& coeff);
	void interpolate(std::vector<double>& lengths, std::vector<double>& values, double* coeff);
	
	void checkShapeFunction(const boost::ptr_vector<AzimuthalAngle>& angles);
	
	double getIncomingCurrent(int ig) const {
		return incomingCurrent[ig];
	}

	void setIndex(int index) {
		this->index = index;
	}
	
	int getIndex() const {
		return index;
	}
	
	void setBoundary(bool boundary) {
		this->boundary = boundary;
	}
	
	bool isBoundary() const {
		return this->boundary;
	}
	
	const CellTypeSurface& getType() const {
		return *type;
	}
	
	void setAdjoint(CellSurface& adjoint) {
		this->adjoint = &adjoint;
	}
	
	CellSurface& getAdjoint() {
		return *(this->adjoint);
	}
	
	void setNeighbor(int leftright, CellSurface& neighbor) {
		this->neighbor[leftright] = &neighbor;
	}

	CellSurface& getNeighbor(int leftright) {
		return *this->neighbor[leftright];
	}
	
};

#endif /* SOLUTION_CELLSURFACE_H_ */
