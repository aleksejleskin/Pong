#ifndef MATH
#define MATH

#include <SDL.h>

namespace Math
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
			vOut.x = this->x +_a.x;
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





	inline SDL_Rect MakeSDLRect(Vector2 _position, float _height, float _width)
	{
		SDL_Rect rect;
		rect.h = (int)_height;
		rect.w = (int)_width;
		rect.x = (int)_position.x;
		rect.y = (int)_position.y;

		return rect;
	}
}

#endif