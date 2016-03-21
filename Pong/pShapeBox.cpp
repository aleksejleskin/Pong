#include "pShapeBox.h"

pShapeBox::pShapeBox(spVector3 _min, spVector3 _max)
{
	m_ShapeType = BOX_SHAPE;
	m_min = _min;
	m_max = _max;
}

pShapeBox::~pShapeBox()
{
}

void pShapeBox::DrawShape(SDL_Renderer * _renderer, DrawHelper * _drawHelper, spVector2 &_position)
{
	_drawHelper->Draw2DBox(_position, spVector2(m_min.x, m_min.y), spVector2(m_max.x, m_max.y), m_DebugDrawColour, 0.0f);
}
