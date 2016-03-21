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
		spVector3 position;
		pShape* collisionShape;

		RigidBodyConstructorInfo(float _mass, spVector3 _position, pShape* _shape)
		{
			mass = _mass;
			position = _position;
			collisionShape = _shape;
		}
	};

	pRigidBody(float _mass, spVector3 _position, pShape* _CollisionShape);
	pRigidBody(const RigidBodyConstructorInfo _RigidBodyInfo);
	~pRigidBody();
	
	//FUCNTIONS
	virtual void CollisionOccured(const CollisionInfo &_info);

	void ApplyImpulse(const spVector3 _forceDirection);
	void CalculateInverseMass();

	void SetMass(float _newMass);
	float GetMass();
	float GetMassInverse();

	pShape* GetShape();
	spVector3 GetPosition();
	void SetPosition(spVector3 _newPos);
	spVector3 GetVelocity();
	float GetRestitution();
	
	void SetUpRigidBody(const RigidBodyConstructorInfo _RigidBodyInfo);
	
	//collision check
	void CollisionStateChanged(bool _isColliding);
	bool m_isColliding;

	pShape* m_CollisionShape;
	spVector3 m_Postion;
	spVector3 m_Scale;
	spVector3	m_Rotation;

	float	m_Mass;
	spVector3 m_LinearVelocity;
	float	m_Restitution;
	spVector3 m_Force;
	float	m_InverseMass;
};

