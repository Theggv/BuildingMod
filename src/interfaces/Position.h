#if !defined(_INTERFACES_POSITION_H_)
#define _INTERFACES_POSITION_H_

#include <pch.h>
#include <math/linear/vec3.h>

using namespace std;

struct Position
{
public:
	/// Position vector
	vec3 pos;

	/// Rotation vector (Uses only y axis)
	vec3 rot;

	Position(vec3 pos, vec3 rot);
};

#endif // _INTERFACES_POSITION_H_
