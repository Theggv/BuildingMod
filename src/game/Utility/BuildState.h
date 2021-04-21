#ifndef _UTILITY_BUILDSTATE_
#define _UTILITY_BUILDSTATE_

#include <pch.h>

enum class BuildState
{
	STATE_NONE,
	STATE_SOLID,
	STATE_CAN_BUILD,
	STATE_CANNOT_BUILD,
};

#endif // !_UTILITY_BUILDSTATE_
