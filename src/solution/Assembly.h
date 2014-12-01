/*
 * Assembly.h
 *
 *  Created on: Oct 17, 2014
 *      Author: jiyoon
 */

#ifndef SOLUTION_ASSEMBLY_H_
#define SOLUTION_ASSEMBLY_H_

#include "../pch.h"
#include "Cell.h"
#include "CellSurface.h"
#include "../geometry/AssemblyType.h"

class Assembly  : public RaysnClass {
private:
	int x;
	int y;
	const AssemblyType* type;
	boost::ptr_vector<CellSurface> 		surfaces;
	boost::ptr_map<int, Cell> 			cells;
	std::map<int, std::string> 	cellNames;
	
	
private:
	int generateKey(int x, int y);
	
public:
	Assembly();
	Assembly(int x, int y, const AssemblyType& type);
	virtual ~Assembly();
	
	void initialize();
	void construct(const boost::ptr_map<const std::string, CellType>& cellTypes, const XSLibrary& xsl);
	void solve(int nIteration, double reigv);
	void generateFunctionalAngularFlux();
	void calculateIncomingCurrent();
	void generateShapeFunction();
	void calculateAverageAngularFlux();
	
	int getX() const {return x;}
	int getY() const {return y;}

	void defineCellType(int x, int y, const std::string cellTypeName);
	void addCell(Cell& cell);
	Cell& getCell(int x, int y);
	
	void updateCrossSection();
	double calculateFissionSource();
	
	void setNeighbor(int NEWS, Assembly& neighbor);
	
	void showResult();
	
	
	
};

#endif /* SOLUTION_ASSEMBLY_H_ */
