#include "PongBall.h"
#include "Wall.h"

#include <iostream>
#include <typeindex>

//(float _mass, spVector3 _position, pShape* _shape)

PongBall::PongBall(const GORigidBodyConstructor &_parameters) : GameObjectRigidBody(_parameters)
{
	m_LastPlayerTouched = nullptr;

	m_RigidBody = new pRigidBody(_parameters.mass, _parameters.position, _parameters.CollisionShape, this);
	_parameters.physics->AddRigidBody(m_RigidBody);
	m_RigidBody->GetShape()->SetShapeDebugDraw(true);
	m_RigidBody->ApplyImpulse(spVector3(10000, 0, 0));
	pRigidBody::CollisionObjectType type = pRigidBody::RIGID_BODY;
	m_RigidBody->SetObjectType(type);
}


PongBall::~PongBall()
{
}


//void CollisionOccured()

//void pongball::collisionoccured(struct collisioninfo &_info)
//{
//
//	std::type_index wall = typeid(class wall);
//	std::type_index playpaddle = typeid(class playerpaddle);
//
//	if (_info.collidedwith != nullptr)
//	{
//		if (dynamic_cast<class wall *>(_info.collidedwith) != 0)
//		{
//			std::cout << "collided with player playerpaddle" << std::endl;
//			if (m_lastplayertouched != nullptr)
//			{
//				m_lastplayertouched->setscore(m_lastplayertouched->getscore() + 1);
//			}
//		}
//
//		if (dynamic_cast<class playerpaddle *>(_info.collidedwith) != 0)
//		{
//			std::cout << "collided with wall" << std::endl;
//			m_lastplayertouched = dynamic_cast<playerpaddle *>(_info.collidedwith);
//		}
//	}
//}