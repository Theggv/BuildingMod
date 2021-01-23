#ifndef _UTILITY_OBSERVABLEVECTOR_
#define _UTILITY_OBSERVABLEVECTOR_

#include <pch.h>
#include "IObserver.h"
#include "IObservable.h"

#include <game/Geometry.h>

using namespace std;

// Observable version of dlls/vector.h
class ObservableVector : public IObservable
{
public:
	// Construction/destruction
	inline ObservableVector() : _x(), _y(), _z() { Notify(); }
	inline ObservableVector(float X, float Y, float Z) : _x(X), _y(Y), _z(Z) { Notify(); }

	inline ObservableVector(const Vector &v)
	{
		*(int *)&_x = *(int *)&v.x;
		*(int *)&_y = *(int *)&v.y;
		*(int *)&_z = *(int *)&v.z;
		Notify();
	}
	inline ObservableVector(const float rgfl[3])
	{
		*(int *)&_x = *(int *)&rgfl[0];
		*(int *)&_y = *(int *)&rgfl[1];
		*(int *)&_z = *(int *)&rgfl[2];
		Notify();
	}

	~ObservableVector();

	// Operators
	inline ObservableVector operator-() const { return ObservableVector(-_x, -_y, -_z); }
	inline int operator==(const ObservableVector &v) const { return _x == v._x && _y == v._y && _z == v._z; }
	inline int operator!=(const ObservableVector &v) const { return !(*this == v); }
	inline ObservableVector operator+(const ObservableVector &v) const { return ObservableVector(_x + v._x, _y + v._y, _z + v._z); }
	inline ObservableVector operator-(const ObservableVector &v) const { return ObservableVector(_x - v._x, _y - v._y, _z - v._z); }
	inline ObservableVector operator*(float fl) const { return ObservableVector(_x * fl, _y * fl, _z * fl); }
	inline ObservableVector operator/(float fl) const { return ObservableVector(_x / fl, _y / fl, _z / fl); }
	inline ObservableVector operator/=(float fl) const { return ObservableVector(_x / fl, _y / fl, _z / fl); }

	// Methods
	inline void CopyToArray(float *rgfl) const
	{
		*(int *)&rgfl[0] = *(int *)&_x;
		*(int *)&rgfl[1] = *(int *)&_y;
		*(int *)&rgfl[2] = *(int *)&_z;
	}
	inline float Length() const { return sqrt(LengthSquared()); }
	inline float LengthSquared() const { return (_x * _x + _y * _y + _z * _z); }

	operator float *() { return &_x; }			   // Vectors will now automatically convert to float * when needed
	operator const float *() const { return &_x; } // Vectors will now automatically convert to float * when needed
	operator Vector() { return Vector(_x, _y, _z); }
	operator vec3() { return vec3(_x, _y, _z); }

	inline Vector ToRound()
	{
		return Vector(
			roundf(_x),
			roundf(_y),
			roundf(_z));
	}

	inline ObservableVector Normalize()
	{
		float flLen = Length();
		if (flLen == 0)
			return ObservableVector(0, 0, 1);

		flLen = 1 / flLen;
		return ObservableVector(_x * flLen, _y * flLen, _z * flLen);
	}
	inline Vector2D Make2D() const
	{
		Vector2D Vec2;
		*(int *)&Vec2.x = *(int *)&_x;
		*(int *)&Vec2.y = *(int *)&_y;
		return Vec2;
	}

	inline float Length2D() const { return sqrt(_x * _x + _y * _y); }

	inline float x() { return _x; }
	inline float y() { return _y; }
	inline float z() { return _z; }

	inline void x(float value)
	{
		_x = value;
		Notify();
	}
	inline void y(float value)
	{
		_y = value;
		Notify();
	}
	inline void z(float value)
	{
		_z = value;
		Notify();
	}

	inline void setVector(float x, float y, float z)
	{
		_x = x;
		_y = y;
		_z = z;
		Notify();
	}

	virtual void Attach(IObserver *observer) override;
	virtual void Detach(IObserver *observer) override;
	virtual void Notify() override;

private:
	float _x, _y, _z;

	list<IObserver *> m_Observers;
};

#endif // !_UTILITY_OBSERVABLEVECTOR_