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
#include "gnuplot-iostream.h"
#include "solution/Problem.h"

using namespace log4cpp;

int main(int argc, const char* argv[]) {
	Appender *	   appender = new OstreamAppender("console",&std::cout);

	PatternLayout* layout = new PatternLayout();
	layout->setConversionPattern("%d %c [%p] %m%n");

	appender->setLayout(layout);

	Category& root = Category::getRoot();

	root.setPriority(log4cpp::Priority::DEBUG);
	root.addAppender(appender);
	
	Problem problem;
	problem.initialize();
	problem.solve();

	pause();

	return 0;
}
