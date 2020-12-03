#ifndef _UTILITY_GEOMETRY_GEOMETRY_H_
#define _UTILITY_GEOMETRY_GEOMETRY_H_

#include <pch.h>

#include "Point.h"
#include "Polygon.h"
#include "Edge.h"
#include "Vertex.h"

enum { INSIDE, OUTSIDE, BOUNDARY };
enum { TOUCHING, CROSSING, INESSENTIAL };

class Geometry
{
public:

	static int PointInPolygon(Point& a, CPolygon& p);
private:
};

#endif // !_UTILITY_GEOMETRY_GEOMETRY_H_
