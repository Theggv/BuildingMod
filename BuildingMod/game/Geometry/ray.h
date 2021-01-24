#ifndef _GAME_GEOMETRY_RAY_H_
#define _GAME_GEOMETRY_RAY_H_

#include <pch.h>
#include "vec3.h"

struct vec3;

struct ray
{
public:
    ray(vec3 origin, vec3 direction, double len = 1e9);

    vec3 GetOrigin();
    vec3 GetDirection();
    vec3 GetDest();
    double GetLength();

    // Rotate direction vector by angle by Z axis
    ray Rotate(double angle);
private:
    vec3 _origin;
    vec3 _direction;
    double _length;
};

#endif // !_GAME_GEOMETRY_RAY_H_