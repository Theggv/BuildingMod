#include "vec2.h"

vec2::vec2(double _x, double _y)
{
	this->x = _x;
	this->y = _y;
}

vec2 vec2::operator+(vec2 &p)
{
	return vec2(x + p.x, y + p.y);
}

vec2 vec2::operator-(vec2 &p)
{
	return vec2(x - p.x, y - p.y);
}

vec2 operator*(double s, vec2 &p)
{
	return vec2(s * p.x, s * p.y);
}

double vec2::operator[](int i)
{
	switch (i)
	{
	case 0:
		return x;
	default:
		return y;
	}
}

int vec2::operator==(vec2 &p)
{
	return (x == p.x) && (y == p.y);
}

int vec2::operator!=(vec2 &p)
{
	return !(*this == p);
}

int vec2::operator<(vec2 &p)
{
	return ((x < p.x) || ((x == p.x) && (y < p.y)));
}

int vec2::operator>(vec2 &p)
{
	return ((x > p.x) || ((x == p.x) && (y > p.y)));
}

double vec2::dot(vec2 &p)
{
	return x * p.x + y * p.y;
}

double vec2::length()
{
	return sqrt(x * x + y * y);
}

vec2 vec2::normalize()
{
	double len = length();

	if (!len)
		return *this;

	return vec2(x / len, y / len);
}

vec2 vec2::GetNormal()
{
	return vec2(y, -x);
}