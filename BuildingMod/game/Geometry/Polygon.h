#ifndef _GAME_GEOMETRY_POLYGON_H_
#define _GAME_GEOMETRY_POLYGON_H_

#include <pch.h>

class vec2;

class Polygon
{
public:
	Polygon();
	Polygon(std::vector<vec2>);

private:
	std::vector<vec2> _points;
};

#endif // !_GAME_GEOMETRY_POLYGON_H_
