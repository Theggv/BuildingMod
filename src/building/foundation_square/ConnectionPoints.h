#if !defined(_FOUNDATION_SQUARE_CONN_POINTS_H_)
#define _FOUNDATION_SQUARE_CONN_POINTS_H_

#include <pch.h>

#include <interfaces/Position.h>
#include <math/linear/linear.h>

enum class FoundationSquareConnectionPoints
{
    UP = 0,
    LEFT = 1,
    DOWN = 2,
    RIGHT = 3,
};

enum class FoundationSquareHeightZones
{
    LOW = 0,
    MIDDLE = 1,
    HIGH = 2,
};

class ConnectionPoints
{
public:
    Position GetRelative(FoundationSquareConnectionPoints point);
    Position GetAbsolute(FoundationSquareConnectionPoints point, vec3 origin, double angle);

private:
    vec3 GetRotation(FoundationSquareConnectionPoints point);
    vec3 GetVector(FoundationSquareConnectionPoints point);
};

#endif // _FOUNDATION_SQUARE_CONN_POINTS_H_
