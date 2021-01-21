#ifndef _GAME_GEOMETRY_MAT4_H_
#define _GAME_GEOMETRY_MAT4_H_

#include <pch.h>

class vec4;

class mat4
{
public:
    mat4(std::vector<double>);

    double operator[](int);
    friend vec4 operator*(vec4 &, mat4 &);

    static mat4 RotationMatrix(double angle);

private:
    double _matrix[16];
};

#endif // !_GAME_GEOMETRY_MAT4_H_