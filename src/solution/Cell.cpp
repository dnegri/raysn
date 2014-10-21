/*
 * Cell.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: jiyoon
 */

#include "Cell.h"
#include "../geometry/RegionType.h"
#include "../quadrature/QuadratureSet.h"

Cell::Cell(int x, int y, FuelCellType& type, XSLibrary& xsl) {

	this->x = x;
	this->y = y;
	
	this->type = &type;
	this->xsl  = &xsl;

	for(RegionType& regionType : type.getRegions()) {
		Region * region = new Region(xsl.getEnergyGroup(), regionType);
		regions.push_back(region);
	}
}

Cell::~Cell() {
}

void Cell::solveOuter(int nout, int nInner) {

	double eigv = 0.0;
	double reigv = 1.0;

	double fissionSource = calculateFissionSource();

	for(int iout=0; iout<nout; iout++) {
		solveInner(nInner, reigv);

		double newFissionSource = calculateFissionSource();

	    double newEigv = eigv*newFissionSource/fissionSource;

	    if(fabs(eigv-newEigv) < MICRO) break;

	    eigv = newEigv;
	    reigv = 1./eigv;
	    fissionSource = newFissionSource;
	}
}

void Cell::solveInner(int nInner, double reigv) {

//	double srcsub[type->get]

	QuadratureSet& quad = QuadratureSet::getInstance();

	CellSurface& startSurface = *surface[initialNEWS];


	for(int ig = 0; ig < xsl->getEnergyGroup(); ig++) {
		for(Region& region : regions) {
			region.calculateSource(ig, reigv);
		}

		for(int in = 0; in<nInner; in++) {
			for(Region& region : regions) {
				region.addSelfScattering(ig);
			}
			
			clearOneGroupFlux(ig);

			for(int is=0; is<NSLOPE; is++) {

				int idxAngle = 0;

				for(AzimuthalAngle& angle : type->getAngles()) {
					std::vector<double**>& angFluxes = startSurface.getAngFlux(idxAngle);

					int idxPoint = 0;
					for(double** angFlux : angFluxes) {

						SurfaceRayPoint* point = &angle.getSurfacePoints().at(idxPoint);
						int islope = is;

						double inAngFlux[quad.getNPolarAngles()];

						for(int ip=0;ip<quad.getNPolarAngles();ip++) {
							inAngFlux[ip] = angFlux[ip][ig];
						}

						while(true) {

							for(Segment& segment : point->getRay(islope).getSegments()) {


								RegionType& regionType = segment.getSubRegion().getRegion();
								Region& region = regions.at(regionType.getIndex());

								int idxSub = segment.getSubRegion().getIndex();
								SubRegion& subRegion = region.getSubRegion(idxSub);

								double source = subRegion.getSource(ig);

								double olen = -region.getCrossSection().getTransport()[ig]*segment.getLength();

								for(int ip=0; ip<quad.getNPolarAngles();ip++) {
									double expo = 1 - exp(olen/quad.getSine(ip));


									double aphio = expo*(inAngFlux[ip] - source);
									double outAngFlux = inAngFlux[ip] - aphio;


									inAngFlux[ip] = outAngFlux;

									double flux = aphio*angle.getRayspace()*angle.getWeight()*quad.getWeight(ip)*quad.getSine(ip);

									subRegion.addOneGroupFlux(ig, flux);
								}
							}

							islope = ~islope;

							point = &point->getEndPoint(islope);

							if(point->getNEWS() == initialNEWS) break;
						}
						
						idxPoint++;
					}

					idxAngle++;
				}

			}

			makeOneGroupFlux(ig);
		}

	}
}

void Cell::clearOneGroupFlux(int group) {
	for(Region& region : regions) {
		region.clearOneGroupFlux(group);
	}
}

void Cell::makeOneGroupFlux( int group) {
	for(Region& region : regions) {
		region.makeOneGroupFlux(group);
	}
}

double Cell::calculateFissionSource() {

	double fissionSource = 0.0;

	for(Region& region : regions) {
		fissionSource+=region.calculateFissionSource();
	}

	return fissionSource;

}

void Cell::updateCrossSection() {

	for(Region& region : regions) {
		region.getCrossSection() = xsl->getCrossSection(0);
	}
	
	regions.at(0).getCrossSection() = xsl->getCrossSection(1);
}
