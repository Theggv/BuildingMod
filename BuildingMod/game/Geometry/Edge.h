#ifndef _GAME_GEOMETRY_EDGE_H_
#define _GAME_GEOMETRY_EDGE_H_

#include <pch.h>
#include "vec2.h"

class Edge
{
public:
	vec2 org;
	vec2 dest;

	Edge(vec2 &_org, vec2 &_dest);
};

#endif // !_GAME_GEOMETRY_EDGE_H_
