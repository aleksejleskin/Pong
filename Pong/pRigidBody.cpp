#include "pRigidBody.h"



pRigidBody::pRigidBody(float _mass, Vector3 _position, pShape* _CollisionShape) 
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

}

void pRigidBody::SetUpRigidBody(const RigidBodyConstructorInfo _RigidBodyInfo)
{
	m_CollisionShape = _RigidBodyInfo.collisionShape;
	m_Postion = _RigidBodyInfo.position;
	m_Mass = _RigidBodyInfo.mass;
	m_Scale = Vector3(.0f, .0f, .0f);
	m_Rotation = Vector3(.0f, .0f, .0f);
	m_Velocity = Vector3(.0f, .0f, .0f);
	m_Restitution = 0.1f;
}

pShape* pRigidBody::GetShape()
{
	return m_CollisionShape;
}

Vector3 pRigidBody::GetPosition()
{
	return m_Postion;
}

Vector3 pRigidBody::GetVelocity()
{
	return m_Velocity;
}

void pRigidBody::SetPosition(Vector3 _newPos)
{
	m_Postion = _newPos;
}

float pRigidBody::GetMass()
{
	return m_Mass;
}

float pRigidBody::GetRestitution()
{
	return m_Restitution;
}