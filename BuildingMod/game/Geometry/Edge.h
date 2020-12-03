#ifndef _UTILITY_GEOMETRY_EDGE_H_
#define _UTILITY_GEOMETRY_EDGE_H_

#include <pch.h>
#include "Point.h"

double dotProduct(Point& p, Point& q);

class Edge
{
public:
	Point org;
	Point dest;

	Edge(Point& _org, Point& _dest);
	Edge(void);

	Edge& rot(void);
	Edge& flip(void);

	Point point(double);

	int intersect(Edge&, double&);
	int cross(Edge&, double&);
	bool isVertical(void);
	double slope(void);
	double ó(double);
};

#endif // !_UTILITY_GEOMETRY_EDGE_H_
