/*
 * CellSurface.cpp
 *
 *  Created on: Oct 17, 2014
 *      Author: jiyoon
 */

#include "CellSurface.h"
#include "../quadrature/QuadratureSet.h"
#include "../util/MatrixVectorOperation.h"

CellSurface::CellSurface() {}


CellSurface::CellSurface(const CellTypeSurface& type, const XSLibrary& xsl, bool boundary) : boundary(boundary), type(&type), xsl(&xsl) {

	int nAngles = type.getNumberOfAngles();
	int nPolar	= QuadratureSet::getInstance().getNPolarAngles();
	
	angularFlux = new SurfaceAngularFlux(boost::extents	[xsl.getEnergyGroup()]
														[nAngles]
														[nPolar]
														[NSLOPE]);
	functionalAngularFlux = new SurfaceAngularFlux(boost::extents	[xsl.getEnergyGroup()]
														[nAngles]
														[nPolar]
														[NSLOPE]);
	
	funtionalCurrents = new boost::multi_array<std::vector<double>*, 2> (boost::extents[xsl.getEnergyGroup()][NSLOPE]);
	
	incomingCurrent = new double[xsl.getEnergyGroup()];
	
	averageAngularFlux = new boost::multi_array<double, 4>(boost::extents[xsl.getEnergyGroup()][nAngles][nPolar][NSLOPE]);
	
	this->xsl = &xsl;
	
	for(int ig=0; ig < xsl.getEnergyGroup(); ig++) {
		for(int ia=0; ia < nAngles; ia++) {
		
			int nPoint = type.getNumberOfPoints(ia);
			
			for(int ip=0; ip < nPolar; ip++) {
				for(int slope=0; slope < NSLOPE; slope++) {
					
					std::vector<double>* flux = new std::vector<double>();
					for(int p=0; p<nPoint; ++p) flux->push_back(1.0);
					
					(*angularFlux)[ig][ia][ip][slope] = *flux;

				}
			}
		}
	}
	
	for(int ig=0; ig < xsl.getEnergyGroup(); ig++) {
		shapeFunction.push_back(new double[3]);
	}
	
}

CellSurface::~CellSurface() {
	if(angularFlux != NULL)
	for(int i=0; i<angularFlux->num_elements(); i++) {
		delete (*angularFlux)[i].origin();
	}

	delete angularFlux;
	
	if(funtionalCurrents != NULL)
	for(int i=0; i<funtionalCurrents->num_elements(); i++) {
		delete (*funtionalCurrents)[i].origin();
	}
	
	delete funtionalCurrents;
	
	for(double* shape : shapeFunction) {
		delete[] shape;
	}
	
}


double CellSurface::getAngFlux(int igroup, const AzimuthalAngle& angle, const SurfaceRayPoint& point, int slope, int ipolar) {
//	return getAngFluxFromShapeFunction(igroup, angle, point, slope, ipolar);
//	return getAngFluxFromFAF(igroup, angle, point, slope, ipolar);
	
	int ia = angle.getIndex();
	int ip = point.getIndex();
	
	std::vector<double>& v = (*angularFlux)[igroup][ia][ipolar][slope];
	
	return v.at(ip);
}

double CellSurface::getAngFluxFromShapeFunction(int igroup, const AzimuthalAngle& angle, const SurfaceRayPoint& point, int slope, int ipolar) {
	int ia = angle.getIndex();
	
	double x = point.getValue(type->getNEWS());
	double factor = shapeFunction[igroup][0];
	
	for(int i=1; i<SHAPE_ORDER; i++) {
		factor += shapeFunction[igroup][i]*pow(x,i);
	}
	
	factor *= (*averageAngularFlux)[igroup][ia][ipolar][slope];
	
	return factor;
}

double CellSurface::getAngFluxFromFAF(int igroup, const AzimuthalAngle& angle, const SurfaceRayPoint& point, int slope, int ipolar) {
	int ia = angle.getIndex();
	
	std::vector<double>& coeff = (*functionalAngularFlux)[igroup][ia][ipolar][slope];
	
	double x = point.getValue(type->getNEWS());
	double aflux = coeff[0];
	
	for(int i=1; i<SHAPE_ORDER; i++) {
		aflux += coeff[i]*pow(x,i);
	}
	
	return aflux;
}



void CellSurface::setAngFlux(int igroup, const AzimuthalAngle& angle, const SurfaceRayPoint& point, int slope, int ipolar, double angFlux) {
	
	int ia = angle.getIndex();
	int ip = point.getIndex();
	
	std::vector<double>& v = (*angularFlux)[igroup][ia][ipolar][slope];
	
	v.at(ip) = angFlux;
}


void CellSurface::calculateAverageAngularFlux(const boost::ptr_vector<AzimuthalAngle>& angles) {
	QuadratureSet& quad = QuadratureSet::getInstance();
	

	for(int ig=0; ig < xsl->getEnergyGroup(); ig++) {
		
		for (const AzimuthalAngle& angle : angles) {
			
			for (int islope = 0; islope < NSLOPE; islope++) {
			
				for(int ip=0; ip<quad.getNPolarAngles(); ip++) {
					
					std::vector<double> v = (*angularFlux)[ig][angle.getIndex()][ip][islope];
					
					double avg = 0.0;
					for(int i = 0; i<v.size(); i++) {
						avg += v[i]*angle.getRayspace()*angle.getReciprocalSinCos(type->getNEWS());
					}
					
					(*averageAngularFlux)[ig][angle.getIndex()][ip][islope] = avg / type->getLength();
				}
			}
		}
	}

	for(int ig=0; ig < xsl->getEnergyGroup(); ig++) {
		
		double incurr = 0.0;
		
		for (const AzimuthalAngle& angle : angles) {
			
			for (int islope = 0; islope < NSLOPE; islope++) {
			
				for(int ip=0; ip<quad.getNPolarAngles(); ip++) {
					
					incurr += (*averageAngularFlux)[ig][angle.getIndex()][ip][islope]*quad.getWeight(ip)*quad.getSine(ip)*angle.getWeight() /
							angle.getReciprocalSinCos(type->getNEWS());
					
				}
			}
		}
		
		logger.debug("AVERAGE ANGULAR FLUX CHECK : %12.5E VS %12.5E", incurr, incomingCurrent[ig]);
		
	}
	
	
}


const double* CellSurface::calculateIncomingCurrent(const boost::ptr_vector<AzimuthalAngle>& angles) {
	QuadratureSet& quad = QuadratureSet::getInstance();
	

	for(int ig=0; ig < xsl->getEnergyGroup(); ig++) {
		
		incomingCurrent[ig] = 0.0;
		
		for (const AzimuthalAngle& angle : angles) {
			
			for (int islope = 0; islope < NSLOPE; islope++) {
			
				for(int ip=0; ip<quad.getNPolarAngles(); ip++) {
					
					std::vector<double> v = (*angularFlux)[ig][angle.getIndex()][ip][islope];
					
					for(int i = 0; i<v.size(); i++) {
						incomingCurrent[ig] += v[i]*quad.getWeight(ip)*quad.getSine(ip)*angle.getWeight()*angle.getRayspace();
					}
				}
			}
		}
		incomingCurrent[ig] /= type->getLength();
	}
	
	return incomingCurrent;
}


void CellSurface::generateShapeFunction() {
	std::vector<double> lengths;
	std::vector<double> values;
	
	lengths.push_back(neighbor[LEFT]->getType().getLength());
	lengths.push_back(getType().getLength());
	lengths.push_back(neighbor[RIGHT]->getType().getLength());
	
	for(int g = 0; g < xsl->getEnergyGroup(); g++) {
		values.push_back(neighbor[LEFT]->getIncomingCurrent(g)/getIncomingCurrent(g));
		values.push_back(1.0);
		values.push_back(neighbor[RIGHT]->getIncomingCurrent(g)/getIncomingCurrent(g));

		interpolate(lengths, values, shapeFunction.at(g));
		
		values.clear();
	}
	
	
}



void CellSurface::generateFunctionalCurrent(const boost::ptr_vector<AzimuthalAngle>& angles) {
//aphin(ip)*polwgt(ip)*aziwgt(iz)*fxrsp(iz)*polsin(ip)
	QuadratureSet& quad = QuadratureSet::getInstance();
	

	for(int ig=0; ig < xsl->getEnergyGroup(); ig++) {
		
		std::vector<double> positions[NSLOPE], values[NSLOPE];
		
		for (const AzimuthalAngle& angle : angles) {
			
			const boost::ptr_vector<SurfaceRayPoint>& points = type->getPoints(angle);
			
			
			for (int islope = 0; islope < NSLOPE; islope++) {
			
				for(int ip=0; ip<quad.getNPolarAngles(); ip++) {
					
					std::vector<double> v = (*angularFlux)[ig][angle.getIndex()][ip][islope];
					
					
					for(int i = 0; i<v.size(); i++) {
						positions[islope].push_back(points.at(i).getValue(type->getNEWS()));
						values[islope].push_back(v[i]*quad.getWeight(ip)*quad.getSine(ip)*angle.getWeight()*angle.getRayspace());
					}
				}
			}
		}
		
		for (int islope = 0; islope < NSLOPE; islope++) {
			std::vector<double>* coeff = new std::vector<double>();
			fitLeastSquare(positions[islope], values[islope], *coeff);
			(*funtionalCurrents)[ig][islope] = coeff;
		}
	}
}

void CellSurface::fitLeastSquare(const std::vector<double>& positions, const std::vector<double>& values, std::vector<double>& coeff) {

	int n = positions.size();
	
	if(n == 2) {
		double slope = (values[1]-values[0]) / (positions[1]-positions[0]);
		coeff.push_back(values[0] - slope*positions[0]);
		coeff.push_back(slope);
		coeff.push_back(0);
		return;
	}
	
	int n0 = n/2;
	
	std::vector<double> tmp(n);
	for(int i = 0; i<n; i++) {
		tmp[i]  = positions[i] - positions[n0];
	}

	double rn = 1. / n;
	
	double x1 = 0;
	for(double pos : positions) x1+=pos;
	
	double x2 = 0;
	for(double pos : positions) x2+=pow(pos,2);

	double x3 = 0;
	for(double pos : positions) x3+=pow(pos,3);

	double x4 = 0;
	for(double pos : positions) x4+=pow(pos,4);

	double xy = 0;
	for(int i = 0; i<n; i++) xy+=positions[i]*values[i];
	
	double y1 = 0;
	for(double val : values) y1+=val;
	
	double x2y = 0;
	for(int i = 0; i<n; i++) x2y += pow(positions[i],2)*values[i];
	
	x1*=rn;
	x2*=rn;
	x3*=rn;
	x4*=rn;
	xy*=rn;
	y1*=rn;
	x2y*=rn;
	
	double bsq   = x1*x1;
	double csq   = x2*x2;
	double dsq   = x3*x3;
	double cdbe  = x2*x3-x1*x4;
	double bcad  = x1*x2-x3;
	double c2bd  = -csq+x1*x3;

	double bunmo = -csq*x2 + 2.0*x1*x2*x3 - dsq - bsq*x4 + x2*x4;
	bunmo = 1. / bunmo;

	coeff.push_back(((-dsq+x2*x4)*y1 +      cdbe*xy +      c2bd*x2y) * bunmo);
	coeff.push_back((        cdbe*y1 + (-csq+x4)*xy +      bcad*x2y) * bunmo);
	coeff.push_back((        c2bd*y1 +      bcad*xy + (-bsq+x2)*x2y) * bunmo);

}

void CellSurface::generateFunctionalAngularFlux(const boost::ptr_vector<AzimuthalAngle>& angles) {
	QuadratureSet& quad = QuadratureSet::getInstance();
	

	for(int ig=0; ig < xsl->getEnergyGroup(); ig++) {
		
		for (const AzimuthalAngle& angle : angles) {
			
			for (int islope = 0; islope < NSLOPE; islope++) {
			
				for(int ip=0; ip<quad.getNPolarAngles(); ip++) {
					
					const std::vector<double>& v = (*angularFlux)[ig][angle.getIndex()][ip][islope];
					
					std::vector<double> pos;
					for(const SurfaceRayPoint& point : type->getPoints(angle)) {
						pos.push_back(point.getValue(type->getNEWS()));
					}
					std::vector<double>& coeff = (*functionalAngularFlux)[ig][angle.getIndex()][ip][islope];
					coeff.clear();
					fitLeastSquare(pos, v, coeff);
				}
			}
		}
	}
}



void CellSurface::interpolate(std::vector<double>& lengths, std::vector<double>& values, double* coeff) {

	
	if(lengths.size() != SHAPE_ORDER) throw std::runtime_error("size of data is not 3 in interpolate of Assembly.");
	
	int size = lengths.size();
	
	double znpos[4];

	znpos[0] = -lengths[0];
	
	for(int i=0; i<size; i++) {
		znpos[i+1] = znpos[i] + lengths[i];
	}
	
	double a[SHAPE_ORDER][SHAPE_ORDER] = {0};
	double b[SHAPE_ORDER]    = {0};
	double sol[SHAPE_ORDER]  = {0};
	
	for(int i=0; i<size; i++) {
		for(int icol=0; icol<size; icol++) {
			a[i][icol] = (pow(znpos[i+1],icol+1) - pow(znpos[i],icol+1)) / (icol+1);
		}
		
		b[i] = values[i]*a[i][0];
	}
	
	MatrixVectorOperation::solveLinearSystem<SHAPE_ORDER>(a, b, sol);
	
	for(int i=0; i<size; i++) {
		coeff[i] = sol[i];
	}

	
}

void CellSurface::checkShapeFunction(const boost::ptr_vector<AzimuthalAngle>& angles) {
	
	QuadratureSet& quad = QuadratureSet::getInstance();
	int index = 0;
	for(int ig = 0; ig < xsl->getEnergyGroup(); ig++) {
		for(int is=0; is<NSLOPE; is++) {
			for(const AzimuthalAngle& angle : angles) {
				for(const SurfaceRayPoint& point : type->getPoints(angle)) {

					const SurfaceRayPoint* pp = &point;
					
					int				 islope = is;
					
					for(int ip=0; ip<quad.getNPolarAngles(); ip++) {
						double ref = getAngFlux(ig, angle, point, islope, ip);
						double shape = getAngFluxFromFAF(ig, angle, point, islope, ip);
						
						logger.info("ANGULAR FLUX COMPARION : %4i %12.5e %12.5e", index++, ref, shape);
					}
				}
			}
		}
	}
}