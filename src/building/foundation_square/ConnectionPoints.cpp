#include "ConnectionPoints.h"
#include <building/constants.h>

Position ConnectionPoints::Get(FoundationSquareConnectionPoints point, vec3 origin, float angle)
{
    vec3 vec = this->GetVector(point);
    vec3 rot = this->GetRotation(point);

    mat4 mat = mat4::RotationMatrix(angle) * mat4::TranslateMatrix(origin);

    return Position(vec.Transform(mat), rot);
}

vec3 ConnectionPoints::GetVector(FoundationSquareConnectionPoints point)
{
    switch (point)
    {
    case FoundationSquareConnectionPoints::LEFT:
        return vec3(-UNIT_SIZE / 2, 0, 0);
    case FoundationSquareConnectionPoints::UP:
        return vec3(0, UNIT_SIZE / 2, 0);
    case FoundationSquareConnectionPoints::RIGHT:
        return vec3(UNIT_SIZE / 2, 0, 0);
    case FoundationSquareConnectionPoints::DOWN:
        return vec3(0, -UNIT_SIZE / 2, 0);
    }

    return vec3::Zero();
}

vec3 ConnectionPoints::GetRotation(FoundationSquareConnectionPoints point)
{
    switch (point)
    {
    case FoundationSquareConnectionPoints::LEFT:
        return vec3(0, -90, 0);
    case FoundationSquareConnectionPoints::UP:
        return vec3(0, 0, 0);
    case FoundationSquareConnectionPoints::RIGHT:
        return vec3(0, 90, 0);
    case FoundationSquareConnectionPoints::DOWN:
        return vec3(0, 180, 0);
    }

    return vec3::Zero();
}
