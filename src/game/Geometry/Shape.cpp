#include "Shape.h"

#include "vec2.h"
#include "mat4.h"

Shape::Shape()
{
}

Shape::Shape(std::vector<vec3> points)
{
    for (auto point : points)
    {
        _initialPoints.push_back(point);
        _transformedPoints.push_back(point);
    }
}

vec3 Shape::GetCenter()
{
    double x = 0, y = 0, z = 0;
    size_t pointsCount = _initialPoints.size();

    for (auto point : _initialPoints)
    {
        x += point.x;
        y += point.y;
        z += point.z;
    }

    return vec3(x / pointsCount, y / pointsCount, z / pointsCount);
}

vec3 Shape::GetPosition()
{
    return _position;
}

void Shape::SetPosition(vec3 pos)
{
    _position = pos;

    Transform();
}

double Shape::GetAngle()
{
    return _angle;
}

void Shape::SetAngle(double angle)
{
    _angle = angle;

    Transform();
}

void Shape::Transform()
{
    auto center = GetCenter();

    auto transformMatrix =
        mat4::TranslateMatrix(-center) *
        mat4::RotationMatrix(_angle) *
        mat4::TranslateMatrix(_position) *
        mat4::TranslateMatrix(center);

    for (size_t i = 0; i < _initialPoints.size(); ++i)
    {
        _transformedPoints[i] = _initialPoints[i].Transform(transformMatrix);
    }
}

/**
 * Пересекаются ли две фигуры
 * https://qastack.ru/gamedev/25397/obb-vs-obb-collision-detection
 * */
bool Shape::IsIntersect(Shape other)
{
    double min1, min2, max1, max2;

    for (size_t i = 0; i < _initialPoints.size(); ++i)
    {
        size_t j = (i == _initialPoints.size() - 1) ? 0 : i + 1;

        auto vec = _initialPoints[i] - _initialPoints[j];
        auto normal = vec2(-vec.y, vec.x);

        SATTest(normal, *this, min1, max1);
        SATTest(normal, other, min2, max2);

        if (!IsValueBetween(min1, min2, max2) && !IsValueBetween(min2, min1, max1))
        {
            return false;
        }
    }

    return true;
}

/**
 * SAT (Separating Axis Theorem) - Способ проверки пересечения двух выпуклых фигур
 * */
void Shape::SATTest(vec2 normal, Shape &polygon, double &min, double &max)
{
    min = INT_MAX;
    max = INT_MIN;

    for (auto point : polygon._initialPoints)
    {
        auto value = vec2::Dot(vec2(point.x, point.y), normal);

        if (value < min)
            min = value;

        if (value > max)
            max = value;
    }
}

bool Shape::IsValueBetween(double value, double min, double max)
{
    return min <= value && value <= max;
}

std::vector<Triangle> Shape::Triangulate()
{
    std::vector<Triangle> triangles;

    if (_initialPoints.size() < 3)
        return triangles;

    for (size_t i = 2; i < _initialPoints.size(); i++)
    {
        triangles.push_back(Triangle(
            _initialPoints[0],
            _initialPoints[i - 1],
            _initialPoints[i]));
    }

    return triangles;
}

std::vector<vec3> Shape::GetPoints(bool transformed)
{
    return transformed ? _transformedPoints : _initialPoints;
}
