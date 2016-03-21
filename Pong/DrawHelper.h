#pragma once
#include <vector>
#include "aMath.h"
using namespace aMath;

class DrawHelper
{
public:
	struct DrawSphereInfo
	{
		spVector2 position;
		float radius;
		SDL_Colour colour;
		int segments;
		float duration;

		DrawSphereInfo(spVector2 _position, float _radius, SDL_Colour _colour, int _segments, float _duration)
		{
			position = _position;
			radius = _radius;
			colour = _colour;
			segments = _segments;
			duration = _duration;
		}
	};

	struct Draw2dBoxInfo
	{
		spVector2 position;
		spVector2 maxExtents;
		spVector2 minExtents;
		SDL_Colour colour;
		float duration;

		Draw2dBoxInfo(spVector2 _position, spVector2 _minExtents, spVector2 _maxExtents, SDL_Colour _colour, float _duration)
		{
			position = _position;
			maxExtents = _maxExtents;
			minExtents = _minExtents;
			colour = _colour;
			duration = _duration;
		}
	};

	std::vector<Draw2dBoxInfo*> m_Draw2dBoxStack;
	std::vector<DrawSphereInfo*> m_DrawCirclesStack;


	DrawHelper();

	~DrawHelper();

	void Draw2DBox(spVector2 _position, spVector2 _minExtents, spVector2 _maxExtents, SDL_Colour _colour,float _duration);
	void Render2DBox(SDL_Renderer *_ren, Draw2dBoxInfo *_2DBox);

	void Draw2DSphere(spVector2 _position, float _radius, SDL_Colour _colour, int _segments, float _duration);
	void Render2DSphere(SDL_Renderer *_ren, DrawSphereInfo *_sphere);
	
	void Render(SDL_Renderer* _renderer);
	void Update(float _deltaTime);
	

	spVector2 Rotate2d(spVector2 _vec, float _angle);
};

