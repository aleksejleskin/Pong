#pragma once
#include "pShape.h"
#include "aMath.h"
using namespace aMath;

class pRigidBody
{
public:

	struct RigidBodyConstructorInfo
	{
		float mass;
		Vector3 position;
		pShape* collisionShape;

		RigidBodyConstructorInfo(float _mass, Vector3 _position, pShape* _shape)
		{
			mass = _mass;
			position = _position;
			collisionShape = _shape;
		}
	};

	pRigidBody(float _mass, Vector3 _position, pShape* _CollisionShape);
	pRigidBody(const RigidBodyConstructorInfo _RigidBodyInfo);

	~pRigidBody();

	pShape* GetShape();
	Vector3 GetPosition();
	void SetPosition(Vector3 _newPos);
	Vector3 GetVelocity();
	float GetRestitution();
	float GetMass();
	void SetUpRigidBody(const RigidBodyConstructorInfo _RigidBodyInfo);


	pShape* m_CollisionShape;
	Vector3 m_Postion;
	Vector3 m_Scale;
	Vector3	m_Rotation;

	float	m_Mass;
	Vector3 m_Velocity;
	float	m_Restitution;

};

