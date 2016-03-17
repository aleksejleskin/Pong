#include "RigidBodyObject.h"
#include <iostream>


using namespace std;

RigidBodyObject::RigidBodyObject(void)
{
	m_Velocity =			Vector2(0.0f,0.0f);
	m_Acceleration =		Vector2(0.0f,0.0f);
	m_Mass =				0.0f;
	m_Force =				Vector2(0.0f, 0.0f);

	m_ApplyImpulse =		false;
	m_ApplyImpulseForce =	Vector2(0.0f, 0.0f);

}

RigidBodyObject::~RigidBodyObject(void)
{
}

void RigidBodyObject::Update(float _dt)
{


	m_Position = m_Position + m_Velocity * _dt;
	m_Velocity = m_Velocity + (m_Force / m_Mass) * _dt;

	if (m_ApplyImpulse)
	{
		m_Force = m_prevForce;
		m_ApplyImpulse = false;
	}

	cout<< "Velocity X: " << m_Velocity.x << " Y: " << m_Velocity.y << endl;
}

void RigidBodyObject::AddForce(Vector2 _force, ForceMode _mode)
{
	switch (_mode)
	{
	case RigidBodyObject::IMPULSE:
		m_ApplyImpulse = true;
		m_prevForce = m_Force;
		m_Force = m_Force + _force;
		break;

	case RigidBodyObject::ADDFORCE:
		m_ApplyImpulse = false;
		m_Force = m_Force +_force;
		break;

	default:
		break;
	}
}

void RigidBodyObject::ApplyImpulse(Vector2 _force)
{
	m_ApplyImpulseForce =	_force;
	m_ApplyImpulse =		true;
}

void RigidBodyObject::SetForce(Vector2 _force)
{
	m_Force = _force;
}
Vector2 RigidBodyObject::GetForce()
{
	return m_Force;
}

void RigidBodyObject::SetMass(float _mass)
{
	m_Mass = _mass;
}

float RigidBodyObject::GetMass()
{
	return m_Mass;
}

Shape RigidBodyObject::GetShape()
{
	return m_Shape;
}