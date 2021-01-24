#ifndef _GAME_GEOMETRY_AABB2_H_
#define _GAME_GEOMETRY_AABB2_H_

#include <pch.h>
#include "vec2.h"

struct vec3;
struct vec4;
struct ray;

struct aabb2
{
public:
    aabb2(vec2 &, vec2 &);

    bool RayIntersection(ray &ray);

    vec2 GetMins();
    vec2 GetMaxs();
private:
    vec2 _mins, _maxs;

    bool LineIntersection(vec2 &a, vec2 &b, vec2 &c, vec2 &d);
    bool _intersection(double a, double b, double c, double d);
    double _area(vec2 a, vec2 b, vec2 c);
};

#endif // !_GAME_GEOMETRY_AABB2_H_