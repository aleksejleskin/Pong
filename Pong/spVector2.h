#pragma once
#include <cmath> 

class spVector2
{
public:

	float x;
	float y;

	spVector2()
	{
		x = 0;
		y = 0;
	}

	spVector2(const float &_x, const float &_y)
	{
		x = _x;
		y = _y;
	}

	__forceinline spVector2& operator += (const spVector2 &_vIn1)
	{
		x += _vIn1.x;
		y += _vIn1.y;
		return *this;
	}

	__forceinline spVector2& operator -= (const spVector2 &_vIn1)
	{
		x -= _vIn1.x;
		y -= _vIn1.y;
		return *this;
	}

	__forceinline spVector2& operator *= (const spVector2 &_vIn1)
	{
		x *= _vIn1.x;
		y *= _vIn1.y;
		return *this;
	}

	__forceinline spVector2& operator /= (const spVector2 &_vIn1)
	{
		x /= _vIn1.x;
		y /= _vIn1.y;
		return *this;
	}

	__forceinline spVector2& operator = (const spVector2 &_vIn1)
	{
		x = _vIn1.x;
		y = _vIn1.y;
		return *this;
	}

	__forceinline spVector2& Normalize()
	{
		return spVector2(
			x / sqrtf(Dot(*this, *this)),
			y / sqrtf(Dot(*this, *this)));
	}

	__forceinline float Length()
	{
		return (sqrtf(Dot(*this, *this)));
	}

	__forceinline float Dot(const spVector2 &_vIn1, const spVector2 &_vIn2)
	{
		return (_vIn1.x * _vIn2.x) + (_vIn1.y * _vIn2.y);
	}
};

__forceinline float Dot(const spVector2 &_vIn1, const spVector2 &_vIn2)
{
	return (_vIn1.x * _vIn2.x) + (_vIn1.y * _vIn2.y);
}

__forceinline spVector2 Clamp( const spVector2 &_vInMin, const spVector2 &_vInMax, const spVector2 &_vInToClamp)
{
	return spVector2(
		_vInToClamp.x < _vInMin.x ? _vInMin.x : _vInToClamp.x > _vInMax.x ? _vInMax.x : _vInToClamp.x,
		_vInToClamp.y < _vInMin.y ? _vInMin.y : _vInToClamp.y > _vInMax.y ? _vInMax.y : _vInToClamp.y);
}

__forceinline spVector2 operator+ (spVector2 &_vIn1, spVector2 &_vIn2)
{
	return spVector2(
		_vIn1.x + _vIn2.x,
		_vIn1.y + _vIn2.y);
}

__forceinline spVector2 operator- (spVector2 &_vIn1, spVector2 &_vIn2)
{
	return spVector2(
		_vIn1.x - _vIn2.x,
		_vIn1.y - _vIn2.y);
}

__forceinline spVector2 operator* (spVector2 &_vIn1, spVector2 &_vIn2)
{
	return spVector2(
		_vIn1.x * _vIn2.x,
		_vIn1.y * _vIn2.y);
}

__forceinline spVector2 operator/ (spVector2 &_vIn1, spVector2 &_vIn2)
{
	return spVector2(
		_vIn1.x / _vIn2.x,
		_vIn1.y / _vIn2.y);
}

__forceinline spVector2 operator+ (spVector2 &_vIn1, float _fIn2)
{
	return spVector2(
		_vIn1.x + _fIn2,
		_vIn1.y + _fIn2);
}

__forceinline spVector2 operator+ (float _fIn1, spVector2 &_vIn2)
{
	return _vIn2 + _fIn1;
}

__forceinline spVector2 operator* (spVector2 &_vIn1, float _fIn2)
{
	return spVector2(
		_vIn1.x * _fIn2,
		_vIn1.y * _fIn2);
}

__forceinline spVector2 operator* (float _fIn1, spVector2 &_vIn2)
{
	return _vIn2 * _fIn1;
}
