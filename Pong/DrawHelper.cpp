#include "DrawHelper.h"



DrawHelper::DrawHelper()
{
}


DrawHelper::~DrawHelper()
{

}

void DrawHelper::Draw2DBox(spVector2 _position, spVector2 _minExtents, spVector2 _maxExtents, SDL_Colour _colour, float _duration)
{
	Draw2dBoxInfo* newDraw2DBox = new Draw2dBoxInfo(_position, _minExtents, _maxExtents, _colour, _duration);

	m_Draw2dBoxStack.push_back(newDraw2DBox);
}

void DrawHelper::Render2DBox(SDL_Renderer *_ren, Draw2dBoxInfo *_2DBox)
{
	spVector2 min = _2DBox->minExtents;
	spVector2 max = _2DBox->maxExtents;
	const int NumBoxCorners = 5;
	spVector2 BoxCorners[NumBoxCorners];

	BoxCorners[0] = min + _2DBox->position;

	BoxCorners[1] = min + _2DBox->position;
	BoxCorners[1].y = max.y + _2DBox->position.y;

	BoxCorners[2] = max + _2DBox->position;

	BoxCorners[3] = max + _2DBox->position;
	BoxCorners[3].y = min.y + _2DBox->position.y;
	//close box
	BoxCorners[4] = min + _2DBox->position;

	for (int corner = 0; corner < 4; corner++)
	{
		int nextCorner = corner + 1;
		if (nextCorner <= NumBoxCorners)
		{

			SDL_RenderDrawLine(_ren, BoxCorners[corner].x, BoxCorners[corner].y, BoxCorners[nextCorner].x, BoxCorners[nextCorner].y);
		}
	}
}

void DrawHelper::Draw2DSphere(spVector2 _position, float _radius, SDL_Colour _colour, int _segments, float _duration)
{
	DrawSphereInfo* newDrawCircle = new DrawSphereInfo(_position, _radius, _colour, _segments, _duration);

	m_DrawCirclesStack.push_back(newDrawCircle);
}

void DrawHelper::Render2DSphere(SDL_Renderer *_ren, DrawSphereInfo *_sphere)
{
	float anglePerSection = 360.0f / _sphere->segments;
	spVector2 startPos, endPos;

	for (int section = 0; section <= _sphere->segments; section++)
	{
		//make sure end point exists.
		if (section + 1 <= _sphere->segments)
		{
			startPos = Rotate2d(spVector2(0, _sphere->radius), anglePerSection * section);
			endPos = Rotate2d(spVector2(0, _sphere->radius), anglePerSection * (section + 1));

			startPos = startPos + _sphere->position;
			endPos = endPos + _sphere->position;

			SDL_RenderDrawLine(_ren, startPos.x, startPos.y, endPos.x, endPos.y);
		}
	}
}

spVector2 DrawHelper::Rotate2d(const spVector2 _vec, float _angle)
{
	double _angleRadians = _angle * 3.14159 / 180.0f;
	spVector2 vOut;
	vOut.x = _vec.x * cosf(_angleRadians) - _vec.y * sinf(_angleRadians);
	vOut.y = _vec.y * cosf(_angleRadians) + _vec.x * sinf(_angleRadians);
	return vOut;
}


void DrawHelper::Update(float _deltaTime)
{
	//m_DrawCirclesStack.clear();
	//m_Draw2dBoxStack.clear();
	for each (DrawSphereInfo* sphere in m_DrawCirclesStack)
	{
		if (sphere != nullptr)
		{
			sphere->duration -= _deltaTime;
		}
	}


	for each (Draw2dBoxInfo* box in m_Draw2dBoxStack)
	{
		if (box != nullptr)
		{
			box->duration -= _deltaTime;
		}
	}
}



void DrawHelper::Render(SDL_Renderer* _renderer)
{
	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(_renderer, &r, &g, &b, &a);

	//draw spheres
	if (m_DrawCirclesStack.empty() == false) 
	{
		for (int i = m_DrawCirclesStack.size() - 1; i >= 0; i--) 
		{
			SDL_SetRenderDrawColor(_renderer, m_DrawCirclesStack.at(i)->colour.r, m_DrawCirclesStack.at(i)->colour.g, m_DrawCirclesStack.at(i)->colour.b, m_DrawCirclesStack.at(i)->colour.a);
			Render2DSphere(_renderer, m_DrawCirclesStack.at(i));

			if (m_DrawCirclesStack.at(i)->duration <= 0) 
			{
				m_DrawCirclesStack.erase(m_DrawCirclesStack.begin() + i);
			}
		}
	}

	//draw boxes.
	if (m_Draw2dBoxStack.empty() == false)
	{
		for (int i = m_Draw2dBoxStack.size() - 1; i >= 0; i--)
		{
			SDL_SetRenderDrawColor(_renderer, m_Draw2dBoxStack.at(i)->colour.r, m_Draw2dBoxStack.at(i)->colour.g, m_Draw2dBoxStack.at(i)->colour.b, m_Draw2dBoxStack.at(i)->colour.a);
			Render2DBox(_renderer, m_Draw2dBoxStack.at(i));

			if (m_Draw2dBoxStack.at(i)->duration <= 0)
			{
				m_Draw2dBoxStack.erase(m_Draw2dBoxStack.begin() + i);
			}
		}
	}


	SDL_SetRenderDrawColor(_renderer, r, g, b, a);
}