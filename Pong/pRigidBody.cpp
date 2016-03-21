#include "pRigidBody.h"



pRigidBody::pRigidBody(float _mass, spVector3 _position, pShape* _CollisionShape) 
{
	RigidBodyConstructorInfo RigidBodyInfo(_mass, _position, _CollisionShape);
	SetUpRigidBody(RigidBodyInfo);
}

pRigidBody::pRigidBody(const RigidBodyConstructorInfo _RigidBodyInfo)
{
	SetUpRigidBody(_RigidBodyInfo);
}

pRigidBody::~pRigidBody()
{
	delete m_CollisionShape;
}

void pRigidBody::SetUpRigidBody(const RigidBodyConstructorInfo _RigidBodyInfo)
{
	m_CollisionShape = _RigidBodyInfo.collisionShape;
	m_Postion = _RigidBodyInfo.position;

	m_Mass = _RigidBodyInfo.mass;
	CalculateInverseMass();

	m_Scale = spVector3(.0f, .0f, .0f);
	m_Rotation = spVector3(.0f, .0f, .0f);
	m_LinearVelocity = spVector3(.0f, .0f, .0f);
	m_Restitution = 1.0f;
	m_Force = spVector3(.0f, .0f, .0f);

	m_isColliding = false;
}

pShape* pRigidBody::GetShape()
{
	return m_CollisionShape;
}

spVector3 pRigidBody::GetPosition()
{
	return m_Postion;
}

spVector3 pRigidBody::GetVelocity()
{
	return m_LinearVelocity;
}

void pRigidBody::SetPosition(spVector3 _newPos)
{
	m_Postion = _newPos;
}

void pRigidBody::SetMass(float _newMass)
{
	m_Mass = _newMass;
	CalculateInverseMass();
}

float pRigidBody::GetMass()
{
	return m_Mass;
}

float pRigidBody::GetRestitution()
{
	return m_Restitution;
}

void pRigidBody::CollisionOccured(const CollisionInfo & _info)
{
}

void pRigidBody::ApplyImpulse(spVector3 _forceDirection)
{
	m_LinearVelocity = m_LinearVelocity + (m_InverseMass * _forceDirection);
}

void pRigidBody::CollisionStateChanged(bool _isColliding)
{
	m_isColliding = _isColliding;
}

float pRigidBody::GetMassInverse()
{
	return m_InverseMass;
}

void pRigidBody::CalculateInverseMass()
{
	//Calcualte inverse mass
	if (m_Mass == 0)
	{
		m_InverseMass = 0;
	}
	else
	{
		m_InverseMass = 1 / m_Mass;
	}
}
