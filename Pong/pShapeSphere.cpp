#include "pShapeSphere.h"


pShapeSphere::pShapeSphere(const float &_radius)
{
	m_ShapeType = SPHERE_SHAPE;
	m_Radius = _radius;
}


pShapeSphere::~pShapeSphere()
{

}

float pShapeSphere::GetRadius()
{
	return m_Radius;
}

void pShapeSphere::DrawShape(SDL_Renderer * _renderer, DrawHelper * _drawHelper, spVector2 &_position)
{
	
	_drawHelper->Draw2DSphere(_position, m_Radius, m_DebugDrawColour, 18,  0.0f);
}