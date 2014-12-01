/*
 * RayInfo.h
 *
 *  Created on: Oct 15, 2014
 *      Author: jiyoon
 */

#ifndef RAYINFO_H_
#define RAYINFO_H_

#include "../pch.h"


class RayInfo  : public RaysnClass {
private:
	int	   nAziAngles;

	double raySpace;

public:
	RayInfo();
	RayInfo(int nAngles, double rayspace);
	virtual ~RayInfo();

	int	 getAziAngles() const;
	void setAziAngles(int aziAngles);

	double getRaySpace() const;
	void   setRaySpace(double raySpace);
};



#endif /* RAYINFO_H_ */
