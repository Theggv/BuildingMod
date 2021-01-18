#include "vec3.h"

vec3::vec3(double _x, double _y, double _z)
{
    this->x = _x;
    this->y = _y;
    this->z = _z;
}

vec3 vec3::operator+(vec3 &p)
{
    return vec3(x + p.x, y + p.y, z + p.z);
}

vec3 vec3::operator-(vec3 &p)
{
    return vec3(x - p.x, y - p.y, z - p.z);
}

vec3 operator*(double s, vec3 &p)
{
    return vec3(s * p.x, s * p.y, s * p.z);
}

double vec3::operator[](int i)
{
    switch (i)
    {
    case 0:
        return x;
    case 1:
        return y;
    default:
        return z;
    }
}

int vec3::operator==(vec3 &p)
{
    return (x == p.x) && (y == p.y) && (z == p.z);
}

int vec3::operator!=(vec3 &p)
{
    return !(*this == p);
}

// rework
int vec3::operator<(vec3 &p)
{
    return ((x < p.x) || ((x == p.x) && (y < p.y)));
}

// rework
int vec3::operator>(vec3 &p)
{
    return ((x > p.x) || ((x == p.x) && (y > p.y)));
}

double vec3::dot(vec3 &p)
{
    return x * p.x + y * p.y + z * p.z;
}

double vec3::length()
{
    return sqrt(x * x + y * y + z * z);
}

vec3 vec3::normalize()
{
    double len = length();

    if (!len)
        return *this;

    return vec3(x / len, y / len, z / len);
}