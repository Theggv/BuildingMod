#include "mat4.h"

#include "vec2.h"
#include "vec3.h"
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
    double angleRad = angleDegrees * acos(0.0) / 90;

    double cos_ = cos(angleRad);
    double sin_ = sin(angleRad);

    return mat4({cos_, -sin_, 0, 0,
                 sin_, cos_, 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1});
}

mat4 mat4::TranslateMatrix(vec2 vec)
{
    return TranslateMatrix(vec3(vec));
}

mat4 mat4::TranslateMatrix(vec3 vec)
{
    return mat4({1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0,
                 vec.x, vec.y, vec.z, 1});
}

double mat4::operator[](int i)
{
    return _matrix[i];
}

vec4 operator*(vec4 vec, mat4 mat)
{
    return vec4(
               vec.x * mat[0] + vec.y * mat[4] + vec.z * mat[8] + vec.w * mat[12],
               vec.x * mat[1] + vec.y * mat[5] + vec.z * mat[9] + vec.w * mat[13],
               vec.x * mat[2] + vec.y * mat[6] + vec.z * mat[10] + vec.w * mat[14],
               vec.x * mat[3] + vec.y * mat[7] + vec.z * mat[11] + vec.w * mat[15])
        .Normalize();
}

mat4 operator*(mat4 a, mat4 b)
{
    return mat4({
        a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12],
        a[0] * b[1] + a[1] * b[5] + a[2] * b[9] + a[3] * b[13],
        a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14],
        a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15],
        a[4] * b[0] + a[5] * b[4] + a[6] * b[8] + a[7] * b[12],
        a[4] * b[1] + a[5] * b[5] + a[6] * b[9] + a[7] * b[13],
        a[4] * b[2] + a[5] * b[6] + a[6] * b[10] + a[7] * b[14],
        a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7] * b[15],
        a[8] * b[0] + a[9] * b[4] + a[10] * b[8] + a[11] * b[12],
        a[8] * b[1] + a[9] * b[5] + a[10] * b[9] + a[11] * b[13],
        a[8] * b[2] + a[9] * b[6] + a[10] * b[10] + a[11] * b[14],
        a[8] * b[3] + a[9] * b[7] + a[10] * b[11] + a[11] * b[15],
        a[12] * b[0] + a[13] * b[4] + a[14] * b[8] + a[15] * b[12],
        a[12] * b[1] + a[13] * b[5] + a[14] * b[9] + a[15] * b[13],
        a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14],
        a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15],
    });
}
