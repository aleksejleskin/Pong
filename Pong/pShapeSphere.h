#pragma once
#include "pShape.h"

class pShapeSphere : public pShape
{
public:
	pShapeSphere(const float &_radius);

	~pShapeSphere();

	float GetRadius();

private:

	float m_Radius;
};

