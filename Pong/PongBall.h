#pragma once
#include "pRigidBody.h"
#include "GameObjectRigidBody.h"

class PongBall : public GameObjectRigidBody
{
public:
	PongBall(const GORigidBodyConstructor &_parameters);
	~PongBall();
};

