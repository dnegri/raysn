/*
 * FuelCellType.cpp
 *
 *  Created on: Oct 11, 2014
 *      Author: jiyoon
 */
#include "FuelCellType.h"
#include "Arc.h"
#include "SubRegionType.h"

FuelCellType::FuelCellType(const double width, const int nRings,
		const std::vector<int>& nSubRings,
		const std::vector<double>& radiuses) {
	this->width = width;
	this->nRings = nRings;
	this->nSubRings = nSubRings;
	this->radiuses = radiuses;

	rwidth = 1. / width;
	hwidth = width * 0.5;
	volume = width * width;
	rvolume = 1. / volume;

	nCircles = accumulate(nSubRings.begin(), nSubRings.end(), 0);

}

FuelCellType::~FuelCellType() {
	// TODO Auto-generated destructor stub
}

double FuelCellType::getRadius(int iCircle) {
	return radiuses.at(iCircle);
}

void FuelCellType::construct(RayInfo& ri) {
	double dtheta = 0.5 * PI / ri.getAziAngles();

	for (int i = 0; i < ri.getAziAngles(); i++) {

		double ang = dtheta * (i + 0.5);
		double npt = width / ri.getRaySpace();
		int nxa = int(sin(ang) * npt);
		int nya = int(cos(ang) * npt);

		nxa = nxa + nxa % 2;
		nya = nya + nya % 2;

		AzimuthalAngle* angle = new AzimuthalAngle();

		ang = atan(width * nxa / (width * nya));

		angle->setAngle(ang);
		angle->setRayspace(
				volume / sqrt(pow(nxa * width, 2.0) + pow(nya * width, 2.0)));
		angle->setPointX(nxa);
		angle->setPointY(nya);

		angles.push_back(angle);

		double dx = width / nxa;
		double x = -dx * 0.5;

		//NORTH
		for (int i = 0; i < nxa; i++) {
			x += dx;
			SurfaceRayPoint* point = new SurfaceRayPoint();
			point->setX(x);
			point->setY(0.0);
			point->setCellSurface(surface[NORTH], NORTH);
			angle->addSurfaceRayPoint(*point);
		}

		//SOUTH
		x = -dx * 0.5;
		for (int i = 0; i < nxa; i++) {
			x += dx;
			SurfaceRayPoint* point = new SurfaceRayPoint();
			point->setX(x);
			point->setY(width);
			point->setCellSurface(surface[SOUTH], SOUTH);
			angle->addSurfaceRayPoint(*point);
		}

		double dy = width / nya;
		double y = -dx * 0.5;

		//WEST
		for (int i = 0; i < nya; i++) {
			y += dy;
			SurfaceRayPoint* point = new SurfaceRayPoint();
			point->setX(0.0);
			point->setY(y);
			point->setCellSurface(surface[WEST], WEST);
			angle->addSurfaceRayPoint(*point);
		}

		//EAST
		y = -dx * 0.5;
		for (int i = 0; i < nya; i++) {
			y += dy;
			SurfaceRayPoint* point = new SurfaceRayPoint();
			point->setX(width);
			point->setY(y);
			point->setCellSurface(surface[EAST], EAST);
			angle->addSurfaceRayPoint(*point);
		}
	}

	AzimuthalAngle& angle1 = angles.at(0);
	AzimuthalAngle& angle2 = angles.at(1);

	double weight = 0.25 * (angle1.getAngle() + angle2.getAngle()) / PI;
	angle1.setWeight(weight);
	angles.end()->setWeight(weight);

	for (int i = 1; i < ri.getAziAngles() - 1; i++) {
		AzimuthalAngle& angle = angles.at(i);
		AzimuthalAngle& angle1 = angles.at(i - 1);
		AzimuthalAngle& angle2 = angles.at(i + 1);

		angle.setWeight(0.25 * (angle2.getAngle() - angle1.getAngle()) / PI);
	}

	corner[NW].setX(0.0);
	corner[NW].setY(0.0);
	corner[NE].setX(width);
	corner[NE].setY(0.0);
	corner[SE].setX(width);
	corner[SE].setY(width);
	corner[SW].setX(0.0);
	corner[SW].setY(width);

	surface[WEST].setBeginPoint(corner[NW]);
	surface[WEST].setEndPoint(corner[SW]);
	surface[EAST].setBeginPoint(corner[NE]);
	surface[EAST].setEndPoint(corner[SE]);
	surface[NORTH].setBeginPoint(corner[NW]);
	surface[NORTH].setEndPoint(corner[NE]);
	surface[SOUTH].setBeginPoint(corner[SW]);
	surface[SOUTH].setEndPoint(corner[SE]);

	initPoints();
	initLines();
	initRegions();
	initSurfaceRays();
}

void FuelCellType::initPoints() {

	Point* point = new Point();
	point->setX(0.0);
	point->setY(0.0);
	points.push_back(point);

	point = new Point();
	point->setX(hwidth);
	point->setY(0.0);
	points.push_back(point);

	point = new Point();
	point->setX(width);
	point->setY(0.0);
	points.push_back(point);

	point = new Point();
	point->setX(width);
	point->setY(hwidth);
	points.push_back(point);

	point = new Point();
	point->setX(width);
	point->setY(width);
	points.push_back(point);

	point = new Point();
	point->setX(hwidth);
	point->setY(width);
	points.push_back(point);

	point = new Point();
	point->setX(0.0);
	point->setY(width);
	points.push_back(point);

	point = new Point();
	point->setX(0.0);
	point->setY(hwidth);
	points.push_back(point);

	for (int i = 0; i < nCircles; i++) {
		for (int idiv = 0; idiv < NDIVREG; idiv++) {
			double ang = PI - (idiv + 1) * 0.25 * PI;

			point = new Point();
			point->setX(hwidth + radiuses.at(i) * cos(ang));
			point->setY(hwidth - radiuses.at(i) * sin(ang));

			points.push_back(point);
		}
	}

	point = new Point();
	point->setX(hwidth);
	point->setY(hwidth);
	points.push_back(point);

	center = *point;
}

void FuelCellType::initLines() {

	// outer surface
	for (int i = 0; i < NDIVREG; i++) {
		Line* line = new Line();
		line->setBeginPoint(points.at(i));
		line->setEndPoint(points.at((i + 1) % NDIVREG));
		lines.push_back(line);
	}

	// inner straight line & curved line
	for (int ir = 0; ir < nCircles; ir++) {

		for (int idiv = 0; idiv < NDIVREG; idiv++) {
			Line* line = new Line();

			int ip = ir * NDIVREG + idiv;
			line->setBeginPoint(points.at(ip));

			ip = ip + NDIVREG;
			line->setEndPoint(points.at(ip));

			lines.push_back(line);
		}

		for (int idiv = 0; idiv < NDIVREG; idiv++) {
			Arc* arc = new Arc();

			int ip = (ir + 1) * NDIVREG + idiv;
			arc->setBeginPoint(points.at(ip));

			ip = (ir + 1) * NDIVREG + (idiv+1) % NDIVREG;
			arc->setEndPoint(points.at(ip));

			arc->setCenter(center);

			arc->setRadius(getRadius(ir));

			lines.push_back(arc);
		}

	}

	//innermost straight line
	for (int idiv = 0; idiv < NDIVREG; idiv++) {
		Line* line = new Line();

		int ip = nCircles * NDIVREG + idiv;
		line->setBeginPoint(points.at(ip));

		ip = std::min<int>(ip + NDIVREG, points.size() - 1);
		line->setEndPoint(points.at(ip));

		lines.push_back(line);
	}

}

void FuelCellType::initRegions() {

	double prevVolume = getVolume();

	for (int ir = 0; ir < nCircles; ir++) {
		double radius = getRadius(ir);
		double volume = PI * pow(radius, 2);

		RegionType * region = new RegionType();
		regions.push_back(region);

		region->setIndex(ir);
		region->setVolume((prevVolume = -volume));

		double subVolume = prevVolume * RDIVREG;

		prevVolume = volume;

		for (int idiv = 0; idiv < NDIVREG; idiv++) {
			SubRegionType* sub = new SubRegionType(*region);

			sub->setIndex(idiv);
			sub->setVolume(subVolume);

			int idxLine = ir * 2 * NDIVREG;

			sub->addEdge(lines.at(idxLine + idiv));

			sub->addEdge(lines.at(idxLine + NDIVREG + idiv));

			sub->addEdge(lines.at(idxLine + NDIVREG + (idiv + 1) % NDIVREG));

			if (nCircles != 0) {
				sub->addEdge(lines.at(idxLine + 2*NDIVREG + idiv));
			}
		}
	}

	RegionType * region = new RegionType();
	regions.push_back(region);

	region->setIndex(nCircles);
	region->setVolume(prevVolume);

	double subVolume = prevVolume * RDIVREG;

	for (int idiv = 0; idiv < NDIVREG; idiv++) {
		SubRegionType* sub = new SubRegionType(*region);

		sub->setVolume(subVolume);

		int idxLine = nCircles * 2 * NDIVREG;

		sub->addEdge(lines.at(idxLine + idiv));

		sub->addEdge(lines.at(idxLine + NDIVREG + idiv));

		sub->addEdge(lines.at(idxLine + NDIVREG + (idiv + 1) % NDIVREG));
	}
}

void FuelCellType::initSurfaceRays() {

	for (int i = 0; i < angles.size(); i++) {

		AzimuthalAngle& ia = angles.at(i);

		boost::ptr_vector<SurfaceRayPoint>& points = ia.getSurfacePoints();

		for (int j = 0; j < points.size(); j++) {
			SurfaceRayPoint& ip = points.at(j);

			Line* subRegionSurface = NULL;
			SubRegionType* subRegion = NULL;
			switch (ip.getNEWS()) {
			case NORTH:
				if (ip.getX() < hwidth) {
					subRegionSurface = &lines.at(0);
					subRegion = &regions.at(0).getSubRegions().at(0);
				} else {
					subRegionSurface = &lines.at(1);
					subRegion = &regions.at(0).getSubRegions().at(1);
				}
				break;
			case EAST:
				if (ip.getY() < hwidth) {
					subRegionSurface = &lines.at(2);
					subRegion = &regions.at(0).getSubRegions().at(2);
				} else {
					subRegionSurface = &lines.at(3);
					subRegion = &regions.at(0).getSubRegions().at(3);
				}
				break;
			case SOUTH:
				if (ip.getX() > hwidth) {
					subRegionSurface = &lines.at(4);
					subRegion = &regions.at(0).getSubRegions().at(4);
				} else {
					subRegionSurface = &lines.at(5);
					subRegion = &regions.at(0).getSubRegions().at(5);
				}
				break;
			case WEST:
				if (ip.getY() > hwidth) {
					subRegionSurface = &lines.at(6);
					subRegion = &regions.at(0).getSubRegions().at(6);
				} else {
					subRegionSurface = &lines.at(7);
					subRegion = &regions.at(0).getSubRegions().at(7);
				}
				break;
			}
			ip.setSubRegionSurface(*subRegionSurface);
			ip.setSubRegion(*subRegion);
			
			double slope = ia.getTangent();
			Line& line = ip.getSurface();
			
			for (int islope = 0; islope < NSLOPE; islope++) {

				for (int inews = 0; inews < NEWS; inews++) {
					
					if (&line == &(surface[inews]))
						continue;

					Point cross;
					double length = 0.0;

					bool crossed = surface[inews].cross(ip, slope,
							ip.getDirection(islope).x,
							ip.getDirection(islope).y, cross, length);

					if (crossed) {
						SurfaceRayPoint& endPoint = ia.findSurfaceRayPoints(
								cross, width, inews);

						ip.setEndPoint(islope, endPoint);
						ip.getRay(islope).setLength(length);

						initSegments(ip, islope, slope);

						break;
					}
				}
				
				slope *= -1;
			}
		}

	}
}

void FuelCellType::initSegments(SurfaceRayPoint& point, int islope,
		double slope) {

	SubRegionType* sub = &point.getSubRegion();

	Point start = point;
	const Line* startLine = &point.getSubRegionSurface();

	while (true) {
		Line* line = NULL;
		Point end;

		for (int i = 0; i < sub->getEdges().size(); i++) {

			line = &sub->getEdges().at(i);
			
			if(startLine == line) continue;

			double length = 0.0;
			bool crossed = line->cross(start, slope,
					point.getDirection(islope).x, point.getDirection(islope).y,
					end, length);

			if (crossed) {
				Segment* segment = new Segment(*sub, length);
				point.getRay(islope).addSegment(*segment);
				break;
			}
		}

		if (end == point.getEndPoint(islope))
			break;

		start = end;
		startLine = line;
		sub = &(line->getNeighborSubRegion(*sub));
	}
}
