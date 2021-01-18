#include "Vertex.h"
#include "Polygon.h"

Vertex::Vertex(double x, double y) : vec2(x, y)
{
}

Vertex::Vertex(vec2 &p) : vec2(p)
{
}