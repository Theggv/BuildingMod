#ifndef _GAME_GEOMETRY_TRIANGLE_H_
#define _GAME_GEOMETRY_TRIANGLE_H_

#include <pch.h>

struct vec3;

struct Triangle
{
public:
    Triangle(vec3 v0, vec3 v1, vec3 v2);

    bool RayIntersection(
        const vec3 rayOrigin,
        const vec3 rayDirection,
        const vec3 &outIntersectionPoint);

private:
    vec3 _v0, _v1, _v2;
};

#endif // !_GAME_GEOMETRY_TRIANGLE_H_
