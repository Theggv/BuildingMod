#include "Shape.h"
#include "vec2.h"

Shape::Shape()
{
}

Shape::Shape(std::vector<vec2> points)
{
    for (auto point : points)
    {
        _points.push_back(point);
    }
}

vec2 Shape::GetCenterPoint()
{
    double x = 0, y = 0;
    size_t pointsCount = _points.size();

    for (auto point : _points)
    {
        x += point.x;
        y += point.y;
    }

    return vec2(x / pointsCount, y / pointsCount);
}

/**
 * Пересекаются ли две фигуры
 * https://qastack.ru/gamedev/25397/obb-vs-obb-collision-detection
 * */
bool Shape::IsIntersect(Shape &other)
{
    double min1, min2, max1, max2;

    for (size_t i = 1; i < _points.size(); ++i)
    {
        auto normal = (_points[i] - _points[i - 1]).NormalVector();

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
    min = INT_MIN;
    max = INT_MAX;

    for (auto point : polygon._points)
    {
        auto value = vec2::Dot(point, normal);

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