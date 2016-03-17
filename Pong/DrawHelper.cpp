#include "DrawHelper.h"



DrawHelper::DrawHelper()
{
}


DrawHelper::~DrawHelper()
{

}

void DrawHelper::Draw2DSphere(Vector2 _position, float _radius, SDL_Colour _colour, int _segments, float _duration)
{
	DrawSphereInfo* newDrawCircle = new DrawSphereInfo(_position, _radius, _colour, _segments, _duration);

	m_DrawCirclesStack.push_back(newDrawCircle);
}

void DrawHelper::Render2DSphere(SDL_Renderer *_ren, DrawSphereInfo *_sphere)
{
	float anglePerSection = 360.0f / _sphere->segments;
	Vector2 startPos, endPos;

	for (int section = 0; section <= _sphere->segments; section++)
	{
		//make sure end point exists.
		if (section + 1 <= _sphere->segments)
		{
			startPos = Rotate2d(Vector2(0, _sphere->radius), anglePerSection * section);
			endPos = Rotate2d(Vector2(0, _sphere->radius), anglePerSection * (section + 1));

			startPos = startPos + _sphere->position;
			endPos = endPos + _sphere->position;

			SDL_RenderDrawLine(_ren, startPos.x, startPos.y, endPos.x, endPos.y);
		}
	}
}

Vector2 DrawHelper::Rotate2d(const Vector2 _vec, float _angle)
{
	double _angleRadians = _angle * 3.14159 / 180.0f;
	Vector2 vOut;
	vOut.x = _vec.x * cosf(_angleRadians) - _vec.y * sinf(_angleRadians);
	vOut.y = _vec.y * cosf(_angleRadians) + _vec.x * sinf(_angleRadians);
	return vOut;
}


void DrawHelper::Update(float _deltaTime)
{
	m_DrawCirclesStack.clear();
	m_DrawCirclesStackToRemove.clear();
	for each (DrawSphereInfo* sphere in m_DrawCirclesStack)
	{
		if (sphere != nullptr)
		{
			sphere->duration -= _deltaTime;
			if (sphere->duration <= .0f)
			{
				m_DrawCirclesStackToRemove.push_back(sphere);
			}
		}
	}
	for each (DrawSphereInfo* sphere in m_DrawCirclesStackToRemove)
	{
		if (sphere != nullptr)
		{
			//delete sphere;
		}
	}
}

void DrawHelper::Render(SDL_Renderer* _renderer)
{
	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(_renderer, &r, &g, &b, &a);

	for each (DrawSphereInfo* sphere in m_DrawCirclesStack)
	{
		if (sphere != nullptr)
		{
			SDL_SetRenderDrawColor(_renderer, sphere->colour.r, sphere->colour.g, sphere->colour.b, sphere->colour.a);
			Render2DSphere(_renderer, sphere);
		}
	}

	SDL_SetRenderDrawColor(_renderer, r, g, b, a);
}