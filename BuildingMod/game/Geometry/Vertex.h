#ifndef _UTILITY_GEOMETRY_VERTEX_H_
#define _UTILITY_GEOMETRY_VERTEX_H_

#include <pch.h>

#include "vec2.h"
#include "Node.h"
#include "Polygon.h"

enum
{
	CLOCKWISE,
	COUNTER_CLOCKWISE
};

class Vertex : public Node, public vec2
{
public:
	Vertex(double x, double y);
	Vertex(vec2 &);
};

#endif // !_UTILITY_GEOMETRY_VERTEX_H_
