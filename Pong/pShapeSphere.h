#pragma once
#include "pShape.h"

class pShapeSphere : public pShape
{
public:
	pShapeSphere(const float &_radius);

	~pShapeSphere();

	void DrawShape(SDL_Renderer * _renderer, DrawHelper * _drawHelper, spVector2 &_position) override;

	float GetRadius();

private:

	float m_Radius;
};

