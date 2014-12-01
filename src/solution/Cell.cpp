/*
 * Cell.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: jiyoon
 */

#include "Cell.h"
#include "../geometry/RegionType.h"
#include "../quadrature/QuadratureSet.h"
#include "BoundaryCondition.h"

Cell::Cell() {}

Cell::Cell(int x, int y, const CellType& type, const XSLibrary& xsl) {

	this->x = x;
	this->y = y;

	this->type = &type;
	this->xsl  = &xsl;
	
	flux = new double[xsl.getEnergyGroup()];

	for(const RegionType& regionType : type.getRegions()) {
		Region * region = new Region(xsl.getEnergyGroup(), regionType);
		regions.push_back(region);
	}
	
	for(int inews=0; inews<NEWS; inews++) {
		surfaces.push_back(new CellSurface(type.getSurface(inews), xsl));
	}
	
}

Cell::~Cell() {
	if(flux != NULL)	delete [] flux;
}

void Cell::solveInner(int nInner, double reigv) {

	QuadratureSet& quad = QuadratureSet::getInstance();
	BoundaryCondition& bc = BoundaryCondition::getInstance();

	CellSurface&   startSurface = surfaces.at(NORTH);
	const CellTypeSurface& surfaceType = startSurface.getType();

	double*			 inAngFlux = new double[quad.getNPolarAngles()];
	
//	gnuplotio::Gnuplot gp;
//
//	gp << "set size square\n";
//	gp << "set xrange [0:"<<type->getXSize()<<"]\n";
//	gp << "set yrange [0:"<<type->getYSize()<<"]\n";

	for(int in = 0; in<nInner; in++) {
		for(int ig = 0; ig < xsl->getEnergyGroup(); ig++) {
			for(Region& region : regions) region.calculateSource(ig, reigv);


//			for(Region& region : regions) region.addSelfScattering(ig);
//
			clearOneGroupFlux(ig);

			for(int is=0; is<NSLOPE; is++) {
			for(const AzimuthalAngle& angle : type->getAngles()) {
			for(const SurfaceRayPoint& point : surfaceType.getPoints(angle)) {

				const SurfaceRayPoint* pp = &point;
				
				int				 islope = is;
				
				for(int ip=0; ip<quad.getNPolarAngles(); ip++) {
					inAngFlux[ip] = startSurface.getAngFlux(ig, angle, point, islope, ip);
				}
				
//				if(angle.getIndex() == 3) {
//				gp << "plot '-' pt 7 ps 1 lc rgb 'blue' with linespoints\n";
//				
//				plotData.push_back(boost::make_tuple(pp->getX(), pp->getY()));
//				}
				
				
				while(true) {

					for(const Segment& segment : pp->getRay(islope).getSegments()) {
					
						
						const RegionType& regionType = segment.getSubRegion().getRegion();
						Region&		region	   = regions.at(regionType.getIndex());

// 						logger.debug("SEGMENT: %3i %12.8f", regionType.getIndex()*8+1+segment.getSubRegion().getIndex(), segment.getLength());
						
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

					const SurfaceRayPoint* end = &(pp->getRay(islope).getEndPoint());
					
//					logger.debug("RT: (%f, %f) to (%f, %f)\t%e\t%e", pp->getX(), pp->getY(), end->getX(), end->getY(),
//									pp->getRay(islope).getLength(), inAngFlux[0]);
					
					int inews = end->getSurface().getNEWS();
					
					//TODO fix setting surface angular flux w.r.t boundary condition.
					if(this->getSurface(inews).isBoundary()) {
						for(int ip=0; ip<quad.getNPolarAngles(); ip++) {
							double f  = bc.getBoundaryFactor(inews);
							this->getSurface(inews).setAngFlux(ig, angle, *end, !islope, ip, f*inAngFlux[ip]);
						}
					} else {
						CellSurface& adjoint = this->getSurface(inews).getAdjoint();
						for(int ip=0; ip<quad.getNPolarAngles(); ip++) {
							adjoint.setAngFlux(ig, angle, *end, islope, ip, inAngFlux[ip]);
						}
					}
					

					if(end->getSurface().getNEWS() == NORTH) break;

					pp = end;
					
					islope = !islope;
					
					for(int ip=0; ip<quad.getNPolarAngles(); ip++) {
						inAngFlux[ip] = this->getSurface(inews).getAngFlux(ig, angle, *pp, islope, ip);
					}
					
					
//				if(angle.getIndex() == 3) {
//					
//					plotData.push_back(boost::make_tuple(pp->getX(), pp->getY()));
//					
//					gp.send1d(plotData);
//					}
					
					
//				if(angle.getIndex() == 3) {
//					gp << "plot '-' pt 7 ps 1 lc rgb 'blue' with linespoints\n";
//}
				}
			}}}

			makeOneGroupFlux(ig);
		}

	}

//	for(Region& region : regions) {
//		for(SubRegion& sub : region.getSubRegions()) {
//			logger.debug("SOURCE: %12.8f", sub.getSource(0));
//		}
//	}
//	
//	
//	for(Region& region : regions) {
//		for(SubRegion& sub : region.getSubRegions()) {
//			logger.debug("FLUX: %12.8f", sub.getFlux(0));
//		}
//	}
//
	delete [] inAngFlux;
	
//	for(int inews=0; inews<NEWS;inews++) {
//		CellSurface* surface = &surfaces[inews];
//		if(!this->getSurface(inews).isBoundary()) {
//			surface = &surfaces[inews].getAdjoint();
//		}
//		surface->generateFunctionalCurrent(type->getAngles());
//	}
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
		region.updateCrossSection(*xsl);
	}
	
}


void Cell::showResult() {
	logger.info("CELL(%2i, %2i) FISSION SOURCE : %12.5e", x+1, y+1, calculateFissionSource());

	for(Region& region : regions) {
		region.showResult();
	}
}


void Cell::calculateIncomingCurrent() {
	for(CellSurface& surface : surfaces) {
		surface.calculateIncomingCurrent(type->getAngles());
	}
}

void Cell::calculateAverageAngularFlux() {
	for(CellSurface& surface : surfaces) {
		surface.calculateAverageAngularFlux(type->getAngles());
	}
}


void Cell::calculateFlux() {
	for(Region& region : regions) {
		region.calculateFlux();
	}
	
	for(int ig=0;ig<xsl->getEnergyGroup();ig++) {
		flux[ig]=0;
		for(Region& region : regions) {
			region.calculateFlux();
			flux[ig] += region.getFlux(ig)*region.getType().getVolume();
		}
		flux[ig] /= type->getVolume();
	}
}

bool Cell::checkNodalBalance(double reigv) {

	
	for(int ig=0;ig<xsl->getEnergyGroup();ig++) {
		double leakage = 0;
		for(int inews=0; inews<NEWS; inews++) {
			if(!surfaces[inews].isBoundary()) {
			leakage += (surfaces[inews].getAdjoint().getIncomingCurrent(ig) - surfaces[inews].getIncomingCurrent(ig)) * surfaces[inews].getType().getLength();
			}
		}
		
		double removal = 0;
		double fission = 0;
		double scattering = 0;
		
		for(Region& region : regions) {
			removal += region.getRemovalTerm(ig);
			fission += reigv*region.getFissionSouce(ig);
			scattering += region.getScatteringSource(ig);
		}
		
		logger.debug("CHECK NODAL BALANCE in CELL (%2i,%2i) FOR GROUP %i", x, y, ig);
		logger.debug("      LEAKAGE : %12.5e", leakage);
		logger.debug("      REMOVAL : %12.5e", removal);
		logger.debug("      FISSION : %12.5e", fission);
		logger.debug("      SCATTER : %12.5e", scattering);
		logger.debug("      BALANCE : %12.5e", (fission+scattering) - (leakage+removal));
		
		
		
	}
	return true;
}


void Cell::checkShapeFunction() {

	for(CellSurface& surface : surfaces) {
		surface.checkShapeFunction(type->getAngles());
	}
}

void Cell::generateShapeFunction() {

	for(CellSurface& surface : surfaces) {
		surface.generateShapeFunction();
	}
}

void Cell::generateFunctionalAngularFlux() {

	for(CellSurface& surface : surfaces) {
		surface.generateFunctionalAngularFlux(type->getAngles());
	}
}