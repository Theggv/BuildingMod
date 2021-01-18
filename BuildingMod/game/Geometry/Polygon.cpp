#include "Polygon.h"
#include "vec2.h"

Polygon::Polygon()
{
}

Polygon::Polygon(std::vector<vec2> points)
{
    for (auto point : points)
    {
        _points.push_back(point);
    }
}