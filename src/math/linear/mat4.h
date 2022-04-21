#ifndef _GAME_GEOMETRY_MAT4_H_
#define _GAME_GEOMETRY_MAT4_H_

#include <pch.h>

struct vec2;
struct vec3;
struct vec4;

struct mat4
{
public:
	mat4(std::vector<double>);

	double operator[](int);
	friend vec4 operator*(vec4, mat4);
	friend mat4 operator*(mat4, mat4);

	static mat4 RotationMatrix(double angle);
	static mat4 TranslateMatrix(vec2);
	static mat4 TranslateMatrix(vec3);

private:
	double _matrix[16];
};

#endif // !_GAME_GEOMETRY_MAT4_H_