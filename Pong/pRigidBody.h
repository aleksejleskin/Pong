#pragma once
#include "pShape.h"
#include "aMath.h"
using namespace aMath;
//
//collision Callback Delegate
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
	
	//FUCNTIONS
	void ApplyImpulse(Vector3 _forceDirection);

	pShape* GetShape();
	Vector3 GetPosition();
	void SetPosition(Vector3 _newPos);
	Vector3 GetVelocity();
	float GetRestitution();
	float GetMass();
	void SetUpRigidBody(const RigidBodyConstructorInfo _RigidBodyInfo);
	float GetMassInverse();
	//collision check
	void CollisionStateChanged(bool _isColliding);
	bool m_isColliding;

	pShape* m_CollisionShape;
	Vector3 m_Postion;
	Vector3 m_Scale;
	Vector3	m_Rotation;

	float	m_Mass;
	Vector3 m_LinearVelocity;
	float	m_Restitution;
	Vector3 m_Force;
	float	m_MassInverse;
};

