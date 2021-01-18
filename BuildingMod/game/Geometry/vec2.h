#ifndef _GAME_GEOMETRY_VEC2_H_
#define _GAME_GEOMETRY_VEC2_H_

#include <pch.h>

class vec2
{
public:
	double x, y;

	vec2(double _x = 0.0, double _y = 0.0);

	// operators

	vec2 operator+(vec2 &);
	vec2 operator-(vec2 &);
	friend vec2 operator*(double, vec2 &);

	double operator[](int);

	int operator==(vec2 &);
	int operator!=(vec2 &);

	int operator<(vec2 &);
	int operator>(vec2 &);

	// methods

	double dot(vec2 &);
	double length();
	vec2 normalize();
};

#endif // !_GAME_GEOMETRY_VEC2_H_
