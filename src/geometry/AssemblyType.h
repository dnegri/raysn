/*
 * Assembly.h
 *
 *  Created on: Oct 17, 2014
 *      Author: jiyoon
 */

#ifndef SOLUTION_ASSEMBLYTYPE_H_
#define SOLUTION_ASSEMBLYTYPE_H_

#include "../pch.h"

class AssemblyType  : public RaysnClass {
private:
	int nxc;
	int nyc;
	std::map<int, std::string> 	cellNames;
	
public:
	AssemblyType(int nxc, int nyc);
	virtual ~AssemblyType();
	
	int		generateKey(int x, int y) const;
	void 	defineCellType(int x, int y, const std::string cellTypeName);
	
	int getNXCell() const {
		return nxc;
	}
	
	int getNYCell() const {
		return nyc;
	}
	
	const std::string& getCellName(int x, int y) const;
};

#endif /* SOLUTION_ASSEMBLYTYPE_H_ */
