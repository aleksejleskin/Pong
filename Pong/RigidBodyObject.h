#pragma once
#include "Object.h"
#include "Collision.h"

class RigidBodyObject : public Object
{
public:
	RigidBodyObject(void);
	~RigidBodyObject(void);

	enum ForceMode
	{
		IMPULSE = 0,
		ADDFORCE = 1
	};

	void		Update(float dt) override;

	void		ApplyImpulse(Vector2 _force);

	void		AddForce(Vector2 _force, ForceMode _mode);
	void		SetForce(Vector2 _force);
	Vector2		GetForce();

	void		SetMass(float _mass);
	float		GetMass();
	Shape		GetShape();

	protected:
	Vector2		m_Velocity;
	Vector2		m_Acceleration;
	float		m_Mass;
	Vector2		m_Force;

	bool		m_ApplyImpulse;
	Vector2		m_ApplyImpulseForce;
	Vector2		m_prevForce;
	Shape		m_Shape;
};

