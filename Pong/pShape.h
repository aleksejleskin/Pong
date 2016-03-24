#pragma once
#include "pGlobal.h"
#include "DrawHelper.h"

class pShape
{

protected:
	int m_ShapeType;
	bool m_DrawShapeDebug;
	SDL_Color m_DebugDrawColour;

public:

	pShape();

	~pShape();

	int GetShapeType();

	virtual void DrawShape(SDL_Renderer * _renderer, DrawHelper * _drawHelper,spVector2 &_position);
	void SetShapeDebugDraw(bool _drawShape);
	void SetShapeDebugDrawColour(const float &r, const float &g, const float &b, const float &a);

};

