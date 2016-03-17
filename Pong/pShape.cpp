#include "pShape.h"

pShape::pShape() : m_ShapeType(INVALID_SHAPE)
{

}


pShape::~pShape()
{
}

int pShape::GetShapeType()
{
	return m_ShapeType;
}