#include "vec4.h"

#include "vec2.h"
#include "vec3.h"
#include "mat4.h"

// constructors

vec4::vec4(double _x, double _y, double _z, double _w) : x(_x), y(_y), z(_z), w(_w)
{
}

vec4::vec4(vec2 vec) : x(vec.x), y(vec.y), z(0), w(1)
{
}

vec4::vec4(vec3 vec) : x(vec.x), y(vec.y), z(vec.z), w(1)
{
}

// methods

vec4 vec4::Normalize()
{
    if (!w)
        return *this;

    return vec4(x / w, y / w, z / w, 1);
}

vec4 vec4::Transform(mat4 mat)
{
    return *this * mat;
}

double vec4::Length()
{
    return sqrt(x * x + y * y + z * z);
}

double vec4::LengthSquared()
{
    return x * x + y * y + z * z;
}

// operators

double vec4::operator[](int i)
{
    switch (i)
    {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    default:
        return w;
    }
}