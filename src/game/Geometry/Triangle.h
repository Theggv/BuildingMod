#ifndef _GAME_GEOMETRY_TRIANGLE_H_
#define _GAME_GEOMETRY_TRIANGLE_H_

#include <pch.h>
#include "vec2.h"
#include "vec3.h"

struct ray;
struct vec2;
struct vec3;
struct mat4;

class FoundationBase;

struct Triangle
{
    friend class VisualizerComponent;

public:
    Triangle(vec3 v0, vec3 v1, vec3 v2);

    Triangle Transform(mat4 mat);

    bool RayIntersection(ray ray, vec3 &outIntersectionPoint);

    /**
	 * Генерирует треугольники для 4 точек a b c d
	 * heights - массив высот [minHeight, maxHeight]
 	 * */
    static std::vector<Triangle> GenerateTriangles(vec2 a, vec2 b, vec2 c, vec2 d, vec2 heights);

private:
    vec3 _v0, _v1, _v2;
};

#endif // !_GAME_GEOMETRY_TRIANGLE_H_
