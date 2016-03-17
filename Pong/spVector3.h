#pragma once

#include <SDL.h>

struct spVector3
{
	float x;
	float y;
	float z;

	spVector3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	spVector3(const float _x, const float _y, const float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	inline spVector3& operator+= (const spVector3& _vIn)
	{
		(x += _vIn.x);
		(y += _vIn.y);
		(z += _vIn.z);
		return *this;
	}

	spVector3& operator+ (const spVector3 &_vIn)
	{
		(x + _vIn.x);
		(y + _vIn.y);
		(z + _vIn.z);
		return *this;
	}

	inline spVector3& operator-= (const spVector3& _vIn)
	{
		(x -= _vIn.x);
		(y -= _vIn.y);
		(z -= _vIn.z);
		return *this;
	}

	spVector3& operator- (const spVector3 &_vIn)
	{
		return spVector3(
			x - _vIn.x,
			y - _vIn.y,
			z - _vIn.z);
	}

	spVector3 operator/= (const spVector3 &_vIn)
	{
		(x /= _vIn.x);
		(y /= _vIn.y);
		(z /= _vIn.z);
		return *this;
	}

	spVector3 operator/ (const spVector3 &_vIn)
	{
		return spVector3(
			x / _vIn.x,
			y / _vIn.y,
			z / _vIn.z);
	}

	inline spVector3& operator*= (const spVector3& _vIn)
	{
		x *= _vIn.x;
		y *= _vIn.y;
		z *= _vIn.z;
		return *this;
	}

	inline spVector3 operator* (const spVector3& _vIn)
	{
		return spVector3(
			x * _vIn.x,
			y * _vIn.y,
			z * _vIn.z);
	}

	spVector3& Normalize()
	{
		spVector3 vOut;
		float length = sqrt(
			(x * x) +
			(y * y) +
			(z * z));

		vOut.x = x / length;
		vOut.y = y / length;
		vOut.z = z / length;
	}
};