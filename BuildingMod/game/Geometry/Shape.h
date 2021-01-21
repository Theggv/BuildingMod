#ifndef _GAME_GEOMETRY_POLYGON_H_
#define _GAME_GEOMETRY_POLYGON_H_

#include <pch.h>

class vec2;

class Shape
{
public:
	Shape();
	Shape(std::vector<vec2> points);

	bool IsIntersect(Shape &other);
	vec2 GetCenterPoint();
private:
	std::vector<vec2> _points;

	void SATTest(vec2 normal, Shape &other, double &min, double &max);
	bool IsValueBetween(double value, double min, double max);
};

#endif // !_GAME_GEOMETRY_POLYGON_H_
