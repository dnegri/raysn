/*
 * CellSurface.cpp
 *
 *  Created on: Oct 17, 2014
 *      Author: jiyoon
 */

#include "CellSurface.h"
#include "../quadrature/QuadratureSet.h"

CellSurface::CellSurface() {}


CellSurface::CellSurface(CellType& type, XSLibrary& xsl, int dirxy) {

	int nAngles = (int)type.getAngles().size();
	int nPolar	= QuadratureSet::getInstance().getNPolarAngles();
	
	angularFlux = new SurfaceAngularFlux(boost::extents	[xsl.getEnergyGroup()]
														[type.getAngles().size()]
														[nPolar]
														[NSLOPE]);
	for(int ig=0; ig < xsl.getEnergyGroup(); ig++) {
	for(int ia=0; ia < nAngles; ia++) {
	for(int k=0; k<nPolar; k++) {
	for(int is=0; is < NSLOPE; is++) {
		int nPoint = 0;

		switch(dirxy) {
		case DIRX:
			nPoint = type.getAngles().at(ia).getPointX();
			break;
		case DIRY:
			nPoint = type.getAngles().at(ia).getPointY();
			break;
		}
		
		std::vector<double>* flux = new std::vector<double>();
		for(int p=0; p<nPoint; ++p) flux->push_back(1.0);
		
		(*angularFlux)[ig][ia][k][is] = *flux;

	}}}}
	
	types.resize(SELFNEIB);
	
}

CellSurface::~CellSurface() {
	if(angularFlux != NULL)
	for(int i=0; i<angularFlux->num_elements(); i++) {
		delete (*angularFlux)[i]     .origin();
	}
}


double CellSurface::getAngFlux(int igroup, AzimuthalAngle& angle, SurfaceRayPoint& point, int islope, int ipolar) {
	int ia = angle.getIndex();
	int ip = point.getIndex();
	
	std::vector<double>& v = (*angularFlux)[igroup][ia][ipolar][islope];
	
	return v.at(ip);
}

void CellSurface::setAngFlux(int igroup, AzimuthalAngle& angle, SurfaceRayPoint& point, int islope, int ipolar, double angFlux) {
	
	int ia = angle.getIndex();
	int ip = point.getIndex();
	
	std::vector<double>& v = (*angularFlux)[igroup][ia][ipolar][islope];
	
	v.at(ip) = angFlux;
}


