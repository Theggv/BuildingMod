#if !defined(_FOUNDATION_SQUARE_CONN_POINTS_H_)
#define _FOUNDATION_SQUARE_CONN_POINTS_H_

#include <pch.h>

#include <interfaces/Position.h>
#include <math/linear/linear.h>

enum class FoundationSquareConnectionPoints
{
    LEFT = 0,
    UP = 1,
    RIGHT = 2,
    DOWN = 3,
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
    Position Get(FoundationSquareConnectionPoints point, vec3 origin, float angle);

private:
    vec3 GetRotation(FoundationSquareConnectionPoints point);
    vec3 GetVector(FoundationSquareConnectionPoints point);
};

#endif // _FOUNDATION_SQUARE_CONN_POINTS_H_
