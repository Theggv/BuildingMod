#ifndef _GAME_GEOMETRY_POLYGON_H_
#define _GAME_GEOMETRY_POLYGON_H_

#include <pch.h>
#include "vec3.h"
#include "Triangle.h"

struct vec2;
struct vec3;

class Shape
{
public:
	Shape();
	Shape(std::vector<vec3> points);

	vec3 GetPosition();
	void SetPosition(vec3);

	double GetAngle();
	void SetAngle(double);

	bool IsIntersect(Shape other);
	vec2 GetCenter();

	std::vector<Triangle> Triangulate();
	/**
	 * Get all points of shape
	 * @param transformed Initial (false) or transformed (true) points 
	 */
	std::vector<vec3> GetPoints(bool transformed = true);

private:
	std::vector<vec3> _initialPoints;
	std::vector<vec3> _transformedPoints;
	vec3 _position;
	double _angle;

	void SATTest(vec2 normal, Shape &other, double &min, double &max);
	bool IsValueBetween(double value, double min, double max);

	// Calls after every change of _position or _angle
	void Transform();
};

#endif // !_GAME_GEOMETRY_POLYGON_H_
