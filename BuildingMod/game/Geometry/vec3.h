#ifndef _GAME_GEOMETRY_VEC3_H_
#define _GAME_GEOMETRY_VEC3_H_

#include <pch.h>

class vec3
{
public:
	double x, y, z;

	vec3(double _x = 0.0, double _y = 0.0, double _z = 0.0);

	// operators

	vec3 operator+(vec3 &);
	vec3 operator-(vec3 &);
	friend vec3 operator*(double, vec3 &);

	double operator[](int);

	int operator==(vec3 &);
	int operator!=(vec3 &);

	int operator<(vec3 &);
	int operator>(vec3 &);

	// methods

	double dot(vec3 &);
	double length();
	vec3 normalize();
};

#endif // _GAME_GEOMETRY_VEC3_H_