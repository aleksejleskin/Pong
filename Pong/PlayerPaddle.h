#pragma once
#include "GameObjectRigidBody.h"

class PlayerPaddle : public GameObjectRigidBody
{
public:
	PlayerPaddle(const GORigidBodyConstructor &_parameters);
	~PlayerPaddle();
};

