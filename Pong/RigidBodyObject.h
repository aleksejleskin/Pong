#pragma once
#include "Object.h"

class RigidBodyObject : public Object
{
public:
	RigidBodyObject(void);
	~RigidBodyObject(void);

	void Update(float dt) override;
	void AddForce(Vector2 _force);
	void SetMass(float _mass);

	protected:
	Vector2 m_Velocity;
	Vector2 m_Acceleration;
	float	m_Mass;

};

