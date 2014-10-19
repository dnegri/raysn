/*
 * CellSurface.cpp
 *
 *  Created on: Oct 17, 2014
 *      Author: jiyoon
 */

#include "CellSurface.h"
#include "../quadrature/QuadratureSet.h"

CellSurface::CellSurface(FuelCellType& type, XSLibrary& xsl, int dirxy) {

	nAngles = type.getAngles().size();
	nPolar  = QuadratureSet::getInstance().getNPolarAngles();

	angFlux = new std::vector<double **>[nAngles];

	for(int i=0; i<type.getAngles().size(); i++) {

		int nPoint = 0;

		switch(dirxy) {
		case DIRX:
			nPoint = type.getAngles().at(i).getPointX();
			break;
		case DIRY:
			nPoint = type.getAngles().at(i).getPointY();
			break;
		}

		angFlux[i].resize(nPoint);

		//TODO check angflux is destroyed when finishing

		for(int j=0; j<nPoint; j++) {

			double ** aFlux = new double*[nPolar];

			for(int k=0; k<nPolar; k++) {
				aFlux[k] = new double[xsl.getEnergyGroup()];
				for(int l=0; l<nPolar; l++) {
					aFlux[k][l] = 1.0;
				}
			}

			angFlux[i].push_back(aFlux);
		}
	}

}

CellSurface::~CellSurface() {

	for(int i=0; i<nAngles; i++) {

		for(int j=0; j<angFlux[i].size(); j++) {

			double ** aFlux = angFlux[i].at(j);

			for(int k=0; k< nPolar; k++) {
				delete [] aFlux[k];
			}
			delete [] aFlux;

		}
	}

}

