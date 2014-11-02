/*
 * Cell.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: jiyoon
 */

#include "Cell.h"
#include "../geometry/RegionType.h"
#include "../quadrature/QuadratureSet.h"

Cell::Cell() {}

Cell::Cell(int x, int y, CellType& type, XSLibrary& xsl) {

	this->x = x;
	this->y = y;

	this->type = &type;
	this->xsl  = &xsl;

	for(RegionType& regionType : type.getRegions()) {
		Region * region = new Region(xsl.getEnergyGroup(), regionType);
		regions.push_back(region);
	}
	
	surfaces.resize(NEWS);
}

Cell::~Cell() {

}

void Cell::solveOuter(int nout, int nInner) {

	double eigv	 = 1.0;
	double reigv = 1.0;

	double fissionSource = calculateFissionSource();

	for(int iout=0; iout<nout; iout++) {
		solveInner(nInner, reigv);

		double newFissionSource = calculateFissionSource();

		double newEigv = eigv*newFissionSource/fissionSource;

		if(fabs(eigv-newEigv) < MICRO) break;

		eigv		  = newEigv;
		reigv		  = 1./eigv;
		fissionSource = newFissionSource;

	}
}

void Cell::solveInner(int nInner, double reigv) {

	QuadratureSet& quad = QuadratureSet::getInstance();

	CellSurface&   startSurface = surfaces.at(NORTH);
	CellTypeSurface& surfaceType = startSurface.getType(SELF);

	double*			 inAngFlux = new double[quad.getNPolarAngles()];
	
//	gnuplotio::Gnuplot gp;
//
//	gp << "set size square\n";
//	gp << "set xrange [0:"<<type->getXSize()<<"]\n";
//	gp << "set yrange [0:"<<type->getYSize()<<"]\n";

	for(int ig = 0; ig < xsl->getEnergyGroup(); ig++) {
		for(Region& region : regions) region.calculateSource(ig, reigv);

		for(int in = 0; in<nInner; in++) {

			for(Region& region : regions) region.addSelfScattering(ig);

			clearOneGroupFlux(ig);

			for(int is=0; is<NSLOPE; is++) {
			for(AzimuthalAngle& angle : type->getAngles()) {
			for(SurfaceRayPoint& point : surfaceType.getPoints(angle)) {

				SurfaceRayPoint* pp = &point;
				
				int				 islope = is;
				
				for(int ip=0; ip<quad.getNPolarAngles(); ip++) {
					inAngFlux[ip] = startSurface.getAngFlux(ig, angle, point, islope, ip);
				}

//				gp << "plot '-' pt 7 ps 1 lc rgb 'blue' with linespoints\n";
				
//				plotData.push_back(boost::make_tuple(pp->getX(), pp->getY()));
				
				
				while(true) {

					for(Segment& segment : pp->getRay(islope).getSegments()) {

						RegionType& regionType = segment.getSubRegion().getRegion();
						Region&		region	   = regions.at(regionType.getIndex());

						int			idxSub	  = segment.getSubRegion().getIndex();
						SubRegion&	subRegion = region.getSubRegion(idxSub);

						double		source = subRegion.getSource(ig);

						double		olen = -region.getCrossSection().getTransport()[ig]*segment.getLength();

						for(int ip=0; ip<quad.getNPolarAngles(); ip++) {
							double expo = 1 - exp(olen/quad.getSine(ip));


							double aphio	  = expo*(inAngFlux[ip] - source);
							double outAngFlux = inAngFlux[ip] - aphio;

							inAngFlux[ip] = outAngFlux;

							double flux = aphio*angle.getRayspace()*angle.getWeight()*quad.getWeight(ip)*quad.getSine(ip);

							subRegion.addOneGroupFlux(ig, flux);
						}
						
					}

					pp = &pp->getRay(islope).getEndPoint();
					
					int inews = pp->getSurface().getNEWS();
					
					//TODO fix setting surface angular flux w.r.t boundary condition.
					for(int ip=0; ip<quad.getNPolarAngles(); ip++) {
						this->getSurface(inews).setAngFlux(ig, angle, *pp, !islope, ip, inAngFlux[ip]);
					}
					
					islope = !islope;
					
					for(int ip=0; ip<quad.getNPolarAngles(); ip++) {
						inAngFlux[ip] = this->getSurface(inews).getAngFlux(ig, angle, *pp, islope, ip);
					}
					
					
//					plotData.push_back(boost::make_tuple(pp->getX(), pp->getY()));
//					
//					gp.send1d(plotData);
					
					if(pp->getSurface().getNEWS() == NORTH) break;
					
//					gp << "plot '-' pt 7 ps 1 lc rgb 'blue' with linespoints\n";

				}
			}}}

			makeOneGroupFlux(ig);
		}

	}
	
	delete [] inAngFlux;
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
		region.setCrossSection(xsl->getCrossSection(0));
	}

	regions.at(0).setCrossSection(xsl->getCrossSection(1));
}
