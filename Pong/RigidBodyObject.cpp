#include "RigidBodyObject.h"
#include <iostream>

using namespace std;

RigidBodyObject::RigidBodyObject(void)
{
	m_Velocity =		Vector2(0.0f,0.0f);
	m_Acceleration =	Vector2(0.0f,0.0f);
	m_Mass =			0.0f;
}

RigidBodyObject::~RigidBodyObject(void)
{
}

void RigidBodyObject::Update(float _dt)
{
	m_Position = m_Position + m_Velocity * _dt;
	m_Velocity = m_Velocity + m_Acceleration * _dt;

	cout<< m_Velocity.x << " " << m_Velocity.y << endl;
	Object::Update(_dt);
}

void RigidBodyObject::AddForce(Vector2 _force)
{
	Vector2 ac = m_Acceleration + _force / m_Mass;
	m_Acceleration = ac;
}

void RigidBodyObject::SetMass(float _mass)
{
	m_Mass = _mass;
}