#include "PhysicsWorld.h"

#include "pGlobal.h"
#include "pShapeBox.h"
#include "pShapeSphere.h"


#include <iostream>
using namespace std;

PhysicsWorld::PhysicsWorld()
{
	m_CollisionCheckArray[0][0] = &PhysicsWorld::AABBtoAABB;
	m_CollisionCheckArray[0][1] = &PhysicsWorld::AABBtoCircle;
	m_CollisionCheckArray[1][0] = &PhysicsWorld::CircletoAABB;
	m_CollisionCheckArray[1][1] = &PhysicsWorld::CircletoCircle;

}


PhysicsWorld::~PhysicsWorld()
{

}

bool PhysicsWorld::CircletoCircle(class pRigidBody *a, class pRigidBody *b)
{
	if (a != nullptr || b != nullptr)
	{
		pShapeSphere *A = (pShapeSphere *)a->GetShape();
		pShapeSphere *B = (pShapeSphere *)b->GetShape();

		Vector3 aPos = a->GetPosition();
		Vector3 bPos = b->GetPosition();

		float r = A->GetRadius() + B->GetRadius();
		r *= r;
		float DistanceX = aPow((aPos.x - bPos.x), 2);
		float DistanceY = aPow((aPos.y - bPos.y), 2);
		return DistanceX + DistanceY <= r;
	}
	else
	{
		return false;
	}
}

bool PhysicsWorld::CircletoAABB(pRigidBody *a, pRigidBody *b)
{

	return false;
}

bool PhysicsWorld::AABBtoAABB(pRigidBody *a, pRigidBody *b)
{

	return false;
}

bool PhysicsWorld::AABBtoCircle(pRigidBody *a, pRigidBody *b)
{

	return false;
}

void PhysicsWorld::ResolveCollision(pRigidBody *a, pRigidBody *b, Vector3 _normal)
{
	// Calculate relative velocity
	Vector3 rv = b->GetVelocity() - a->GetVelocity();

		// Calculate relative velocity in terms of the normal direction
	float velAlongNormal = DotProduct(rv, _normal);

		// Do not resolve if velocities are separating
	//if (!velAlongNormal > 0)
	{
		//return;

// Calculate restitution
		float e = Min(a->GetRestitution(), a->GetRestitution());

		// Calculate impulse scalar
		float j = (1 + e) * -1 * velAlongNormal;
			j /= 1 / a->m_Mass + 1 / b->m_Mass;

		// Apply impulse
		Vector3 impulse = j * _normal;

		Vector3 newVela = 1 / a->GetMass() * impulse;
		a->m_LinearVelocity = a->m_LinearVelocity - newVela;

		Vector3 newVelb = 1 / b->GetMass() * impulse;
		b->m_LinearVelocity = b->m_LinearVelocity + newVelb;
	}
}

void PhysicsWorld::EulerStep(float _deltaTick, pRigidBody * _rigidBody)
{
	Vector3 newPos = _rigidBody->m_LinearVelocity * _deltaTick;
	_rigidBody->m_Postion = _rigidBody->m_Postion + newPos;

	Vector3 newVel  = (1 / _rigidBody->m_Mass * _rigidBody->m_Force) * _deltaTick;
	_rigidBody->m_LinearVelocity = _rigidBody->m_LinearVelocity + newVel;
}

pRigidBody* PhysicsWorld::CreateRigidBody(float _mass, Vector3 _position, pShape* _Shape)
{
	pRigidBody::RigidBodyConstructorInfo RigidBodyInfo(_mass, _position, _Shape);
	pRigidBody * newRigidBody = new pRigidBody(RigidBodyInfo);

	m_RigidBodyList.push_back(newRigidBody);

	return newRigidBody;
}

void PhysicsWorld::stepSimulation(float _deltaTick)
{

	for each (pRigidBody* obj1 in m_RigidBodyList)
	{
		EulerStep(_deltaTick, obj1);

		for each (pRigidBody* obj2 in m_RigidBodyList)
		{
			if (obj1 != obj2)
			{
				if((this->*m_CollisionCheckArray[obj1->GetShape()->GetShapeType()][obj2->GetShape()->GetShapeType()])(obj1, obj2))
				{
					obj1->CollisionStateChanged(true);
					obj2->CollisionStateChanged(true);

					Vector3 direction = obj2->GetPosition() - obj1->GetPosition();
					Vector3 normal = direction.Normalize();
					ResolveCollision(obj1, obj2, normal);
					//std::cout << "COLLIDING" << endl;
				}
				else
				{
					obj1->CollisionStateChanged(false);
					obj2->CollisionStateChanged(false);
					//std::cout << "NOT COLLIDING" <<endl;
				}
			}
		}
	}
}