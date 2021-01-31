#include "ray.h"
#include "mat4.h"

ray::ray(vec3 origin, vec3 direction, double len)
    : _origin(origin), _direction(direction.Normalize()), _length(len)
{
}

vec3 ray::GetOrigin()
{
    return _origin;
}

vec3 ray::GetDirection()
{
    return _direction;
}

double ray::GetLength()
{
    return _length;
}

double ray::GetVectorAngle()
{
    // special cases
    if (_origin.x == 0)
        return (_origin.y > 0)
                   ? 90
               : (_origin.y == 0) ? 0
                                  : 270;
    else if (_origin.y == 0)
        return (_origin.x >= 0) ? 0 : 270;

    auto ret = atan(_origin.y / _origin.x);

    if (_origin.x < 0 && _origin.y < 0) // quadrant Ⅲ
        ret = 180 + ret;
    else if (_origin.x < 0)     // quadrant Ⅱ
        ret = 180 + ret;        // it actually substracts
    else if (_origin.y < 0)     // quadrant Ⅳ
        ret = 270 + (90 + ret); // it actually substracts

    return ret;
}

vec3 ray::GetDest()
{
    return _origin + _direction * _length;
}

ray ray::Rotate(double angle)
{
    return ray(_origin, _direction.Transform(mat4::RotationMatrix(angle)), _length);
}
