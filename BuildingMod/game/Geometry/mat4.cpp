#include <math.h>

#include "mat4.h"
#include "vec4.h"

using namespace std;

mat4::mat4(std::vector<double> matrix)
{
    for (size_t i = 0; i < 16; ++i)
    {
        _matrix[i] = matrix[i];
    }
}

mat4 mat4::RotationMatrix(double angleDegrees)
{
    double angleRad = angleDegrees * M_PI / 180;

    return mat4({cos(angleRad), -sin(angleRad), 0, 0,
                 sin(angleRad), cos(angleRad), 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1});
}

double mat4::operator[](int i)
{
    return _matrix[i];
}

vec4 operator*(vec4 &vec, mat4 &mat)
{
    return vec4(
               vec.x * mat[0] + vec.y * mat[4] + vec.z * mat[8] + vec.w * mat[12],
               vec.x * mat[1] + vec.y * mat[5] + vec.z * mat[9] + vec.w * mat[13],
               vec.x * mat[2] + vec.y * mat[6] + vec.z * mat[10] + vec.w * mat[14],
               vec.x * mat[3] + vec.y * mat[7] + vec.z * mat[11] + vec.w * mat[15])
        .Normalize();
}
