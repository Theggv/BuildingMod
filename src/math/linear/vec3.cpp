#include "vec3.h"

#include "vec2.h"
#include "vec4.h"
#include "mat4.h"

// constructors

vec3::vec3(double _x, double _y, double _z) : x(_x), y(_y), z(_z)
{
}

vec3::vec3(vec2 vec) : x(vec.x), y(vec.y), z(0)
{
}

vec3::vec3(Vector vec) : x(vec.x), y(vec.y), z(vec.z)
{
}

// static methods

vec3 vec3::One()
{
	return vec3(1, 1, 1);
}

vec3 vec3::UnitX()
{
	return vec3(1, 0, 0);
}

vec3 vec3::UnitY()
{
	return vec3(0, 1, 0);
}

vec3 vec3::UnitZ()
{
	return vec3(0, 0, 1);
}

vec3 vec3::Zero()
{
	return vec3(0, 0, 0);
}

double vec3::Distance(vec3 a, vec3 b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

double vec3::DistanceSquared(vec3 a, vec3 b)
{
	return pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2);
}

double vec3::Dot(vec3 a, vec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

vec3 vec3::Cross(vec3 a, vec3 b)
{
	return vec3(
		a.y * b.z - b.y * a.z,
		a.z * b.x - b.z * a.x,
		a.x * b.y - b.x * a.y);
}

// methods

vec3 vec3::Abs()
{
	return vec3(abs(x), abs(y), abs(z));
}

vec3 vec3::Normalize()
{
	auto len = Length();

	if (!len)
		return *this;

	return vec3(x / len, y / len, z / len);
}

vec3 vec3::Round()
{
	return vec3(roundf(x), roundf(y), roundf(z));
}

vec3 vec3::Transform(mat4 mat)
{
	auto vec = vec4(*this) * mat;

	return vec3(vec.x, vec.y, vec.z);
}

double vec3::Length()
{
	return sqrt(x * x + y * y + z * z);
}

double vec3::LengthSquared()
{
	return x * x + y * y + z * z;
}

// operators

double vec3::operator[](int i)
{
	switch (i)
	{
	case 0:
		return x;
	case 1:
		return y;
	default:
		return z;
	}
}

vec3 vec3::operator+(vec3 vec)
{
	return vec3(x + vec.x, y + vec.y, z + vec.z);
}

vec3 vec3::operator-()
{
	return vec3(-x, -y, -z);
}

vec3 vec3::operator-(vec3 vec)
{
	return vec3(x - vec.x, y - vec.y, z - vec.z);
}

vec3 operator*(double s, vec3 vec)
{
	return vec3(s * vec.x, s * vec.y, s * vec.z);
}

vec3 operator*(vec3 vec, double s)
{
	return vec3(s * vec.x, s * vec.y, s * vec.z);
}

vec3 operator/(vec3 vec, double s)
{
	return vec3(vec.x / s, vec.y / s, vec.z / s);
}

bool vec3::operator==(vec3& vec)
{
	return IsEqual(x, vec.x) && IsEqual(y, vec.y) && IsEqual(z, vec.z);
}

bool vec3::operator!=(vec3& vec)
{
	return !(*this == vec);
}