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

vec3 ray::GetDest()
{
    return _origin + _direction * _length;
}

ray ray::Rotate(double angle)
{
    return ray(_origin, _direction.Transform(mat4::RotationMatrix(angle)), _length);
}
