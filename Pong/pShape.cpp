#include "pShape.h"


pShape::pShape() : m_ShapeType(INVALID_SHAPE)
{
	m_DrawShapeDebug = false;
	m_DebugDrawColour.a = 0;
	m_DebugDrawColour.r = 255;
	m_DebugDrawColour.g = 0;
	m_DebugDrawColour.b = 0;
}


pShape::~pShape()
{
}

int pShape::GetShapeType()
{
	return m_ShapeType;
}

void pShape::SetShapeDebugDraw(bool _drawShape)
{
	m_DrawShapeDebug = _drawShape;
}

void pShape::DrawShape(SDL_Renderer * _renderer, DrawHelper * _drawHelper, spVector2 &_position)
{

}

void pShape::SetShapeDebugDrawColour(const float &r, const float &g, const float &b, const float &a)
{
	m_DebugDrawColour.a = a;
	m_DebugDrawColour.r = r;
	m_DebugDrawColour.g = g;
	m_DebugDrawColour.b = b;
}