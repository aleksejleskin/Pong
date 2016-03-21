#pragma once

//included due to sqrt use, need custom float implementation.
#include <SDL.h>

class spVector3
{
public:

	float x;
	float y;
	float z;

	//Default constructor initializes vector components to zero
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

	__forceinline spVector3& operator+= (const spVector3& _vIn)
	{
		x += _vIn.x;
		y += _vIn.y;
		z += _vIn.z;
		return *this;
	}

	__forceinline spVector3& operator-= (const spVector3& _vIn)
	{
		x -= _vIn.x;
		y -= _vIn.y;
		z -= _vIn.z;
		return *this;
	}

	__forceinline spVector3& operator/= (const spVector3 &_vIn)
	{
		x /= _vIn.x;
		y /= _vIn.y;
		z /= _vIn.z;
		return *this;
	}

	__forceinline spVector3& operator*= (const spVector3& _vIn)
	{
		x *= _vIn.x;
		y *= _vIn.y;
		z *= _vIn.z;
		return *this;
	}

	__forceinline spVector3 Normalize()
	{
		return spVector3(
		x / sqrtf(Dot(*this, *this)),
		y / sqrtf(Dot(*this, *this)),
		z / sqrtf(Dot(*this, *this)));
	}

	__forceinline float Length()
	{
		return (sqrtf(Dot(*this, *this)));
	}

private:
	//some fucntions must operate on the spVector3 obejct for ease of use, but consist of other 
	__forceinline float Dot(const spVector3 &_vIn1, const spVector3 &_vIn2)
	{
		return (_vIn1.x * _vIn2.x + _vIn1.y * _vIn2.y + _vIn1.z * _vIn2.z);
	}
};

__forceinline float Dot(const spVector3 &_vIn1, const spVector3 &_vIn2)
{
	return (_vIn1.x * _vIn2.x + _vIn1.y * _vIn2.y + _vIn1.z * _vIn2.z);
}

__forceinline spVector3 operator+ (const spVector3 &_vIn1, const spVector3 &_vIn2)
{
	return spVector3(
		_vIn1.x + _vIn2.x,
		_vIn1.y + _vIn2.y,
		_vIn1.z + _vIn2.z);
}

__forceinline spVector3 operator- (const spVector3 &_vIn1, const spVector3 &_vIn2)
{
	return spVector3(
		_vIn1.x - _vIn2.x,
		_vIn1.y - _vIn2.y,
		_vIn1.z - _vIn2.z);
}

__forceinline spVector3 operator* (const spVector3 &_vIn1, const spVector3 &_vIn2)
{
	return spVector3(
		_vIn1.x * _vIn2.x,
		_vIn1.y * _vIn2.y,
		_vIn1.z * _vIn2.z);
}

__forceinline spVector3 operator/ (const spVector3 &_vIn1, const spVector3 &_vIn2)
{
	return spVector3(
		_vIn1.x / _vIn2.x,
		_vIn1.y / _vIn2.y,
		_vIn1.z / _vIn2.z);
}

//Multiply each vector components by the input float, output new vector.
__forceinline spVector3 operator* (const spVector3 &_vIn1, const float &_fIn2)
{
	return spVector3(
		_vIn1.x * _fIn2,
		_vIn1.y * _fIn2,
		_vIn1.z * _fIn2);
}

//implementation vector * float already exists, will call existing function.
__forceinline spVector3 operator* (const float &_fIn1, const spVector3 &_vIn2)
{
	return _vIn2 * _fIn1;
}

//If all coresponding components are of the same value, then vectors are equal, return true
__forceinline bool operator== (const spVector3 &_vIn1, const spVector3 &_vIn2)
{
	return (
		(_vIn1.x == _vIn2.x) &&
		(_vIn1.y == _vIn2.y) &&
		(_vIn1.z == _vIn2.z));
}