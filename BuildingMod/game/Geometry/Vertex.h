#ifndef _UTILITY_GEOMETRY_VERTEX_H_
#define _UTILITY_GEOMETRY_VERTEX_H_

#include <pch.h>

#include "Point.h"
#include "Node.h"
#include "Polygon.h"

enum { CLOCKWISE, COUNTER_CLOCKWISE };

class Vertex : public Node, public Point {
public:
	Vertex(double x, double y);
	Vertex(Point&);
	Vertex* cw(void);
	Vertex* ccw(void);
	Vertex* neighbor(int rotation);
	Point point(void);
	Vertex* insert(Vertex*);
	Vertex* remove(void);
	void splice(Vertex*);
	Vertex* split(Vertex*);
	friend class CPolygon;
};

#endif // !_UTILITY_GEOMETRY_VERTEX_H_
