#pragma once
#include "pRigidBody.h"
#include "GameObjectRigidBody.h"
#include "PlayerPaddle.h"

class pRigidBody;

class PongBall : public GameObjectRigidBody
{
public:
	PongBall(const GORigidBodyConstructor &_parameters);
	~PongBall();

	PlayerPaddle *m_LastPlayerTouched;
};
