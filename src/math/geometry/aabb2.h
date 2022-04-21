#ifndef _GAME_GEOMETRY_AABB2_H_
#define _GAME_GEOMETRY_AABB2_H_

#include <pch.h>

#include "../linear/linear.h"
#include "Ray.h"

struct aabb2
{
public:
    aabb2(vec2, vec2);

    bool RayIntersection(Ray ray);

    vec2 GetMins();
    vec2 GetMaxs();

private:
    vec2 _mins, _maxs;

    bool LineIntersection(vec2 a, vec2 b, vec2 c, vec2 d);
    bool _intersection(double a, double b, double c, double d);
    double _area(vec2 a, vec2 b, vec2 c);
};

#endif // !_GAME_GEOMETRY_AABB2_H_