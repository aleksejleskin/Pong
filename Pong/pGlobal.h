#pragma once
//#include "aMath.h"
#include "spVector3.h"
//#include "pRigidBody.h"
//using namespace aMath;

enum CollisionShapesTypes
{
	
	BOX_SHAPE = 0,
	SPHERE_SHAPE = 1,

	INVALID_SHAPE
};

struct CollisionInfo
{
	spVector3 ImpactPoint;
	spVector3 ImpactNormal;
	//pRigidBody * CollidedWith;
};


