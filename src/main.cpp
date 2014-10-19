/*
 * main.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jiyoon
 */

#include "pch.h"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/PatternLayout.hh"
#include "geometry/FuelCellType.h"
#include "solution/Cell.h"
#include "xs/XSLibrary.h"

using namespace log4cpp;

int main(int argc, const char* argv[]) {
	Appender * appender = new OstreamAppender("console",&std::cout);

	PatternLayout* layout = new PatternLayout();
	layout->setConversionPattern("%d %c [%p] %m%n");

	appender->setLayout(layout);

	Category& root = Category::getRoot();

	root.setPriority(log4cpp::Priority::DEBUG);
	root.addAppender(appender);

	double width = 1.28776;
	int nRings = 1;

	std::vector<int> nSubRings;
	nSubRings.push_back(1);

	std::vector<double> radiuses;
	radiuses.push_back(0.41275);

	FuelCellType fuelCellType(width, nRings, nSubRings, radiuses);
	XSLibrary xsl;
	RayInfo rayInfo(4, 8, 0.2);

	fuelCellType.construct(rayInfo);

	Cell cell(fuelCellType, xsl);

	cell.solveOuter(100, 2);

	return 0;
}
