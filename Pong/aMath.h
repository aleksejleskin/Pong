#ifndef AMATH
#define AMATH

#include <SDL.h>
#include "spVector3.h"

namespace aMath
{

	struct Vector3
	{
		Vector3()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}

		Vector3(float _x, float _y, float _z)
		{
			x = _x;
			y = _y;
			z = _z;
		}
		float x;
		float y;
		float z;

		Vector3 operator- (const Vector3& _a)
		{
			Vector3 vOut;
			vOut.x = this->x + _a.x;
			vOut.y = this->y + _a.y;
			vOut.z = this->z + _a.z;
			return vOut;
		}

		Vector3 operator* (const float& _a)
		{
			Vector3 vOut;
			vOut.x = this->x * _a;
			vOut.y = this->y * _a;
			vOut.z = this->z * _a;
			return vOut;
		}

		Vector3 operator-= (const Vector3& _b)
		{
			Vector3 vOut;
			vOut.x = this->x - _b.x;
			vOut.y = this->y - _b.y;
			vOut.z = this->z - _b.z;
			return vOut;
		}

		Vector3 operator+= (const Vector3& _b)
		{
			Vector3 vOut;
			vOut.x = this->x + _b.x;
			vOut.y = this->y + _b.y;
			vOut.z = this->z + _b.z;
			return vOut;
		}

		Vector3 operator+ (const Vector3& _b)
		{
			Vector3 vOut;
			vOut.x = this->x + _b.x;
			vOut.y = this->y + _b.y;
			vOut.z = this->z + _b.z;
			return vOut;
		}

		Vector3 operator/ (const float& _b)
		{
			Vector3 vOut;
			vOut.x = this->x / _b;
			vOut.y = this->y / _b;
			vOut.z = this->z / _b;
			return vOut;
		}

		Vector3 Normalize()
		{
			Vector3 vOut;
			float 	length = sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
			//normalized vector
			vOut.x = this->x / length;
			vOut.y = this->y / length;
			vOut.z = this->z / length;
			return	vOut;
		}
	};

	struct Vector2
	{
		Vector2()
		{
			x = 0.0f;
			y = 0.0f;
		}
		Vector2(float _x, float _y)
		{
			x = _x;
			y = _y;
		}
		float x;
		float y;

		Vector2 operator+ (const Vector2& _a)
		{
			Vector2 vOut;
			vOut.x = this->x + _a.x;
			vOut.y = this->y + _a.y;
			return vOut;
		}

		Vector2 operator/ (const float& _a)
		{
			Vector2 vOut;
			vOut.x = x / _a;
			vOut.y = y / _a;
			return vOut;
		}

		Vector2 operator* (const float& _a)
		{
			Vector2 vOut;
			vOut.x = x * _a;
			vOut.y = y * _a;
			return vOut;
		}

		void operator= (const Vector2& _a)
		{
			//Vector2 vOut;
			//vOut.x =  _a.x;
			//vOut.y = _a.y;
			//return vOut;
			this->x = _a.x;
			this->y = _a.y;
		}
	};

	inline float DotProduct(Vector3 _vec1, Vector3 _vec2)
	{
		float outValue = 0;
		outValue += _vec1.x * _vec2.x;
		outValue += _vec1.y * _vec2.y;
		outValue += _vec1.z * _vec2.z;
		return outValue;
	}

	inline double aPow(double _value, int _powerOf)
	{
		double outValue = _value;

		for (int times = 1; times < _powerOf; times++)
		{
			outValue *= _value;
		}
		return outValue;
	}

	inline SDL_Rect MakeSDLRect(Vector2 _position, float _height, float _width)
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


	inline Vector3 operator* (const float _a, const Vector3 B)
	{
		Vector3 vOut;
		vOut.x = B.x * _a;
		vOut.y = B.y * _a;
		vOut.z = B.z * _a;
		return vOut;
	}

}

#endif