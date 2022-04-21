#ifndef _GAME_GEOMETRY_VEC4_H_
#define _GAME_GEOMETRY_VEC4_H_

#include <pch.h>

struct vec2;
struct vec3;
struct mat4;

struct vec4
{
public:
	double x, y, z, w;

	vec4(double _x = 0.0, double _y = 0.0, double _z = 0.0, double _w = 1.0);
	vec4(vec2);
	vec4(vec3);

	// methods

	vec4 Normalize();

	vec4 Transform(mat4);

	double Length();
	double LengthSquared();

	// operators

	double operator[](int);
};

#endif // !_GAME_GEOMETRY_VEC4_H_
