#pragma once
#include <vector>
#include "aMath.h"
using namespace aMath;

class DrawHelper
{
public:
	struct DrawSphereInfo
	{
		Vector2 position;
		float radius;
		SDL_Colour colour;
		int segments;
		float duration;

		DrawSphereInfo(Vector2 _position, float _radius, SDL_Colour _colour, int _segments, float _duration)
		{
			position = _position;
			radius = _radius;
			colour = _colour;
			segments = _segments;
			duration = _duration;
		}
	};

	std::vector<DrawSphereInfo*> m_DrawCirclesStack;
	std::vector<DrawSphereInfo*> m_DrawCirclesStackToRemove;


	DrawHelper();

	~DrawHelper();

	void Draw2DSphere(Vector2 _position, float _radius, SDL_Colour _colour, int _segments, float _duration);

	void Render(SDL_Renderer* _renderer);
	void Update(float _deltaTime);
	void Render2DSphere(SDL_Renderer *_ren, DrawSphereInfo *_sphere);

	Vector2 Rotate2d(Vector2 _vec, float _angle);
};

