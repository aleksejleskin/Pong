#pragma once
#include "aMath.h"
using namespace aMath;

enum CollisionShapesTypes
{
	
	BOX_SHAPE = 0,
	SPHERE_SHAPE = 1,

	INVALID_SHAPE
};

struct CollisionInfo
{
	Vector3 ImpactPoint;
	Vector3 ImpactNormal;
};


