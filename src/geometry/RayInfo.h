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
	int	   nAziAnglesX2;

	double raySpace;

public:
	RayInfo();
	RayInfo(int, int, double);
	virtual ~RayInfo();

	int	 getAziAngles() const;
	void setAziAngles(int aziAngles);

	int	 getAziAnglesX2() const;
	void setAziAnglesX2(int aziAnglesX2);

	double getRaySpace() const;
	void   setRaySpace(double raySpace);
};



#endif /* RAYINFO_H_ */
