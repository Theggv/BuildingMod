#include "vec2.h"

#include "mat4.h"
#include "vec3.h"
#include "vec4.h"

// constructors

vec2::vec2(double _x, double _y) : x(_x), y(_y)
{
}

vec2::vec2(vec3 vec) : x(vec.x), y(vec.y)
{
}

// static methods

vec2 vec2::One()
{
	return vec2(1, 1);
}

vec2 vec2::UnitX()
{
	return vec2(1, 0);
}

vec2 vec2::UnitY()
{
	return vec2(0, 1);
}

vec2 vec2::Zero()
{
	return vec2(0, 0);
}

double vec2::Distance(vec2 a, vec2 b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double vec2::DistanceSquared(vec2 a, vec2 b)
{
	return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
}

double vec2::Dot(vec2 a, vec2 b)
{
	return a.x * b.x + a.y * b.y;
}

// methods

vec2 vec2::Abs()
{
	return vec2(abs(x), abs(y));
}

vec2 vec2::Normalize()
{
	auto len = Length();

	if (!len)
		return *this;

	return vec2(x / len, y / len);
}

vec2 vec2::NormalVector()
{
	return vec2(y, -x);
}

vec2 vec2::Round()
{
	return vec2(roundf(x), roundf(y));
}

vec2 vec2::Transform(mat4 mat)
{
	auto vec = vec4(*this) * mat;

	return vec2(vec.x, vec.y);
}

double vec2::Length()
{
	return sqrt(x * x + y * y);
}

double vec2::LengthSquared()
{
	return x * x + y * y;
}

// operators

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

vec2 vec2::operator+(vec2 vec)
{
	return vec2(x + vec.x, y + vec.y);
}

vec2 operator-(const vec2 vec)
{
	return vec2(-vec.x, -vec.y);
}

vec2 operator-(vec2 a, vec2 b)
{
	return vec2(a.x - b.x, a.y - b.y);
}

vec2 operator*(double s, vec2 vec)
{
	return vec2(s * vec.x, s * vec.y);
}

vec2 operator*(vec2 vec, double s)
{
	return vec2(s * vec.x, s * vec.y);
}

vec2 operator/(vec2 vec, double s)
{
	return vec2(vec.x / s, vec.y / s);
}

bool vec2::operator==(vec2& vec)
{
	return IsEqual(x, vec.x) && IsEqual(y, vec.y);
}

bool vec2::operator!=(vec2& vec)
{
	return !(*this == vec);
}