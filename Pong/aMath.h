#ifndef AMATH
#define AMATH

#include <SDL.h>
#include "spVector3.h"
#include "spVector2.h"
#include "spScalar.h"

namespace aMath
{
	//struct spVector2
	//{
	//	spVector2()
	//	{
	//		x = 0.0f;
	//		y = 0.0f;
	//	}
	//	spVector2(float _x, float _y)
	//	{
	//		x = _x;
	//		y = _y;
	//	}
	//	float x;
	//	float y;

	//	spVector2 operator+ (const spVector2& _a)
	//	{
	//		spVector2 vOut;
	//		vOut.x = this->x + _a.x;
	//		vOut.y = this->y + _a.y;
	//		return vOut;
	//	}

	//	spVector2 operator/ (const float& _a)
	//	{
	//		spVector2 vOut;
	//		vOut.x = x / _a;
	//		vOut.y = y / _a;
	//		return vOut;
	//	}

	//	spVector2 operator* (const float& _a)
	//	{
	//		spVector2 vOut;
	//		vOut.x = x * _a;
	//		vOut.y = y * _a;
	//		return vOut;
	//	}

	//	void operator= (const spVector2& _a)
	//	{
	//		//spVector2 vOut;
	//		//vOut.x =  _a.x;
	//		//vOut.y = _a.y;
	//		//return vOut;
	//		this->x = _a.x;
	//		this->y = _a.y;
	//	}
	//};

	inline double aPow(double _value, int _powerOf)
	{
		double outValue = _value;

		for (int times = 1; times < _powerOf; times++)
		{
			outValue *= _value;
		}
		return outValue;
	}

	inline SDL_Rect MakeSDLRect(spVector2 _position, float _height, float _width)
	{
		SDL_Rect rect;
		rect.h = (int)_height;
		rect.w = (int)_width;
		rect.x = (int)_position.x;
		rect.y = (int)_position.y;

		return rect;
	}

	inline float Min(float _value1, float _value2)
	{
		return _value1 < _value2 ? _value1 : _value2;
	}

}

#endif