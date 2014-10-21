/*
 * QuadratureSet.h
 *
 *  Created on: Oct 10, 2014
 *      Author: jiyoon
 */

#ifndef QUADRATURESET_H_
#define QUADRATURESET_H_

class QuadratureSet {

private:
	int		nPolarAngles;
	double* weights;
	double* angles;
	double* sins;

private:
	QuadratureSet(int nPolarAngles=3);
public:
	static QuadratureSet& getInstance() {
		static QuadratureSet instance;
		return instance;
	}
	virtual ~QuadratureSet();

	double getAngle(int ip) const {
		return angles[ip];
	}

	int getNPolarAngles() const {
		return nPolarAngles;
	}

	double getSine(int ip) const {
		return sins[ip];
	}

	double getWeight(int ip) const {
		return weights[ip];
	}
};

#endif /* QUADRATURESET_H_ */
