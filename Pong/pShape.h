#pragma once
#include "pGlobal.h"

class pShape
{
protected:
	int m_ShapeType;

public:

	pShape();

	~pShape();

	int GetShapeType();
};

