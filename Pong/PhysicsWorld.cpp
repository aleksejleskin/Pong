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

bool PhysicsWorld::CircletoCircle(pRigidBody *a, pRigidBody *b)
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
	//	if (velAlongNormal > 0)
			//return;

	// Calculate restitution
	float e = Min(a->GetRestitution(), a->GetRestitution());

		// Calculate impulse scalar
	float j = -(1 + e) * velAlongNormal;
	j /= 1 / a->GetMass() + 1 / b->GetMass();

		// Apply impulse
	Vector3 impulse = j * _normal;
	
	a->m_Velocity -= 1 / a->m_Mass * impulse;
	b->m_Velocity += 1 / b->m_Mass * impulse;
}

pRigidBody* PhysicsWorld::CreateRigidBody(float _mass, Vector3 _position, pShape* _Shape)
{
	pRigidBody::RigidBodyConstructorInfo RigidBodyInfo(_mass, _position, _Shape);
	pRigidBody * newRigidBody = new pRigidBody(RigidBodyInfo);

	m_RigidBodyList.push_back(newRigidBody);

	return newRigidBody;
}

void PhysicsWorld::stepSimulation()
{
	for each (pRigidBody* obj1 in m_RigidBodyList)
	{
		for each (pRigidBody* obj2 in m_RigidBodyList)
		{
			if (obj1 != obj2)
			{

				if((this->*m_CollisionCheckArray[obj1->GetShape()->GetShapeType()][obj2->GetShape()->GetShapeType()])(obj1, obj2))
				{
					int  a = 5;
				}
				else
				{
					int  a = 5;
				}
			}
		}
	}
}