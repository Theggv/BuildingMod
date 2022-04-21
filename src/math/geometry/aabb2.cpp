#include "aabb2.h"

aabb2::aabb2(vec2 p1, vec2 p2)
{
    _mins = vec2(min(p1.x, p2.x), min(p1.y, p2.y));
    _maxs = vec2(max(p1.x, p2.x), max(p1.y, p2.y));
}

vec2 aabb2::GetMins()
{
    return _mins;
}

vec2 aabb2::GetMaxs()
{
    return _maxs;
}

bool aabb2::RayIntersection(Ray ray)
{
    auto start = vec2(ray.GetOrigin());
    auto end = vec2(ray.GetDest());

    return LineIntersection(start, end, _mins, vec2(_mins.x, _maxs.y)) ||
           LineIntersection(start, end, _mins, vec2(_maxs.x, _mins.y)) ||
           LineIntersection(start, end, _maxs, vec2(_mins.x, _maxs.y)) ||
           LineIntersection(start, end, _maxs, vec2(_maxs.x, _mins.y));
}

bool aabb2::LineIntersection(vec2 a, vec2 b, vec2 c, vec2 d)
{
    const double eps = 0.0000001;

    return _intersection(a.x, b.x, c.x, d.x) &&
           _intersection(a.y, b.y, c.y, d.y) &&
           _area(a, b, c) * _area(a, b, d) <= eps &&
           _area(c, d, a) * _area(c, d, b) <= eps;
}

bool aabb2::_intersection(double a, double b, double c, double d)
{
    if (a > b)
        std::swap(a, b);
    if (c > d)
        std::swap(c, d);

    return max(a, c) <= min(b, d);
}

double aabb2::_area(vec2 a, vec2 b, vec2 c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}