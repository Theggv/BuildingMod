#ifndef _GAME_GEOMETRY_VEC3_H_
#define _GAME_GEOMETRY_VEC3_H_

#include <pch.h>

struct vec2;
struct mat4;

struct vec3
{
public:
    double x, y, z;

    vec3(double _x = 0.0, double _y = 0.0, double _z = 0.0);
    vec3(vec2);
    vec3(Vector);

    // static methods

    static vec3 One();
    static vec3 UnitX();
    static vec3 UnitY();
    static vec3 UnitZ();
    static vec3 Zero();

    static double Distance(vec3, vec3);
    static double DistanceSquared(vec3, vec3);

    static double Dot(vec3, vec3);
    static vec3 Cross(vec3, vec3);

    // methods

    vec3 Abs();
    vec3 Normalize();
    vec3 Round();

    vec3 Transform(mat4);

    double Length();
    double LengthSquared();

    // operators

    double operator[](int);

    vec3 operator+(vec3);

    vec3 operator-();
    vec3 operator-(vec3);

    friend vec3 operator*(double, vec3);
    friend vec3 operator*(vec3, double);

    friend vec3 operator/(vec3, double);

    int operator==(vec3);
    int operator!=(vec3);
};

#endif // !_GAME_GEOMETRY_VEC3_H_
