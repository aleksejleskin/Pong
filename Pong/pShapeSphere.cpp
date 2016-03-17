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