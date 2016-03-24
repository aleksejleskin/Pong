#pragma once
#include "pShape.h"
class pShapeBox : public pShape
{
public:
	pShapeBox(spVector3 _extents);

	~pShapeBox();

	void DrawShape(SDL_Renderer * _renderer, DrawHelper * _drawHelper, spVector2 &_position) override;

	spVector3 m_min;
	spVector3 m_max;
};



