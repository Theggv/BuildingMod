#include "Triangle.h"
#include "ray.h"
#include "mat4.h"

Triangle::Triangle(vec3 v0, vec3 v1, vec3 v2)
    : _v0(v0), _v1(v1), _v2(v2)
{
}

void Triangle::Transform(mat4 &mat)
{
    _v0 = _v0.Transform(mat);
    _v1 = _v1.Transform(mat);
    _v2 = _v2.Transform(mat);
}

// Möller–Trumbore intersection algorithm
bool Triangle::RayIntersection(
    ray &ray,
    vec3 &outIntersectionPoint)
{
    const float EPS = 0.00000001;

    vec3 edge1 = _v1 - _v0;
    vec3 edge2 = _v2 - _v0;
    vec3 pvec = vec3::Cross(ray.GetDirection(), edge2);

    float det = vec3::Dot(edge1, pvec);

    if (det > -EPS && det < EPS)
        return false;

    float invDet = 1.0f / det;
    vec3 tvec = ray.GetOrigin() - _v0;
    float u = invDet * vec3::Dot(tvec, pvec);

    if (u < 0.0 || u > 1.0)
        return false;

    vec3 qvec = vec3::Cross(tvec, edge1);
    float v = invDet * vec3::Dot(ray.GetDirection(), qvec);

    if (v < 0.0 || u + v > 1.0)
        return false;

    float t = invDet * vec3::Dot(edge2, qvec);

    if (t > EPS)
    {
        outIntersectionPoint = ray.GetOrigin() + ray.GetDirection() * t;
        return true;
    }

    return false;
}