#include "pShapeBox.h"

pShapeBox::pShapeBox(spVector3 _extents)
{
	m_ShapeType = BOX_SHAPE;
	m_max = spVector3(_extents.x, _extents.y, _extents.z);
	m_min = m_max * -1;
}

pShapeBox::~pShapeBox()
{
}

void pShapeBox::DrawShape(SDL_Renderer * _renderer, DrawHelper * _drawHelper, spVector2 &_position)
{
	_drawHelper->Draw2DBox(_position, spVector2(m_min.x, m_min.y), spVector2(m_max.x, m_max.y), m_DebugDrawColour, 0.0f);
}
