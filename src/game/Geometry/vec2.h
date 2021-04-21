#ifndef _GAME_GEOMETRY_VEC2_H_
#define _GAME_GEOMETRY_VEC2_H_

#include <pch.h>

struct vec3;
struct mat4;

struct vec2
{
public:
	double x, y;

	vec2(double _x = 0.0, double _y = 0.0);
	vec2(vec3);

	// static methods

	static vec2 One();
	static vec2 UnitX();
	static vec2 UnitY();
	static vec2 Zero();

	static double Distance(vec2, vec2);
	static double DistanceSquared(vec2, vec2);

	static double Dot(vec2, vec2);

	// methods

	vec2 Abs();
	vec2 Normalize();
	vec2 NormalVector();
	vec2 Round();

	vec2 Transform(mat4);

	double Length();
	double LengthSquared();

	// operators

	double operator[](int);

	vec2 operator+(vec2);

	friend vec2 operator-(const vec2);
	friend vec2 operator-(vec2, vec2);

	friend vec2 operator*(double, vec2);
	friend vec2 operator*(vec2, double);

	friend vec2 operator/(vec2, double);

	int operator==(vec2);
	int operator!=(vec2);
};

#endif // !_GAME_GEOMETRY_VEC2_H_
