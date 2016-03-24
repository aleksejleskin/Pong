#include "PhysicsWorld.h"
#include "pGlobal.h"
#include "pShapeBox.h"
#include "pShapeSphere.h"
#include "aMath.h"
#include <amp.h>
#include <iostream>
using namespace std;
using namespace aMath;

PhysicsWorld::PhysicsWorld()
{
	//Collision jump table, each eigid body has a type, on each update type is checked,
	//Collision is resolved by pointing to the propert function from this array.
	m_CollisionCheckArray[0][0] = &PhysicsWorld::AABBtoAABB;
	m_CollisionCheckArray[0][1] = &PhysicsWorld::AABBtoCircle;
	m_CollisionCheckArray[1][0] = &PhysicsWorld::CircletoAABB;
	m_CollisionCheckArray[1][1] = &PhysicsWorld::CircletoCircle;

	_ColInfo = new pRigidBody::CollisionInfo();
}


PhysicsWorld::~PhysicsWorld()
{
	for each (pRigidBody *obj in m_RigidBodyList)
	{
		if (obj != nullptr)
		{
			delete(obj);
		}
	}
	m_RigidBodyList.clear();

	delete(_ColInfo);
}

bool PhysicsWorld::CircletoCircle(class pRigidBody *a, class pRigidBody *b, struct pRigidBody::CollisionInfo * _info)
{
	//dont check collision if input is invalid.
	if (a != nullptr || b != nullptr)
	{
		pShapeSphere *A = (pShapeSphere *)a->GetShape();
		pShapeSphere *B = (pShapeSphere *)b->GetShape();

		spVector3 aPos = a->GetPosition();
		spVector3 bPos = b->GetPosition();

		float r = A->GetRadius() + B->GetRadius();
		r *= r;
		float DistanceX = aPow((aPos.x - bPos.x), 2);
		float DistanceY = aPow((aPos.y - bPos.y), 2);

		//Check if collision occured
		if (DistanceX + DistanceY <= r)
		{
			//collision info set back to each obejct
			pRigidBody::CollisionInfo objAInfo;

			//if objects are not inside each other
			float distance = (aPos - bPos).Length();
			//objAInfo.CollidedWith = b;

			if (distance != 0)
			{
				objAInfo.ImpactNormal = aPos - bPos;
				objAInfo.ImpactPoint = (aPos - bPos) * A->GetRadius();
			}
			else
			{
				objAInfo.ImpactPoint = spVector3(0, 0, 0);
				objAInfo.ImpactNormal = spVector3(1, 0, 0);
			}
			a->CollisionOccured(objAInfo);

			spVector3 direction = b->GetPosition() - a->GetPosition();
			spVector3 normal = direction.Normalize();
			//update velocities based on collision
			ResolveCollision(a, b, normal);
			_info->ImpactNormal = normal;
			_info->CollidedWith = b;
			return true;
		}
		else
		{
			return false;
		}

	}
	else
	{
		return false;
	}
}

bool PhysicsWorld::CircletoAABB( class pRigidBody *aRigidBody,  class pRigidBody *bRigidBody, pRigidBody::CollisionInfo * _info)
{
		// Setup a couple pointers to each object
		pShapeSphere *ASphereShape = (pShapeSphere *)aRigidBody->GetShape();
		pShapeBox *BBoxShape = (pShapeBox *)bRigidBody->GetShape();

		spVector2 circleCenterPos = spVector2(aRigidBody->GetPosition().x, aRigidBody->GetPosition().y);
		spVector2 boxCenterPos = spVector2(bRigidBody->GetPosition().x, bRigidBody->GetPosition().y);

		spVector2 ShapeFromCenterDistnace = boxCenterPos - circleCenterPos;

		//position box at 0,0,0
		//coutn circle position to be the distance from the box, 
		//(transform everything into local space, and coutn box to be at 0,0,0
		spVector2 circleLocalPos = ShapeFromCenterDistnace;
		spVector2 aabb_half_extents = spVector2(BBoxShape->m_max.x, BBoxShape->m_max.y);

		//collision point projected onto box.
		spVector2 collisionPointProject = Clamp(aabb_half_extents* -1, aabb_half_extents, ShapeFromCenterDistnace);



		//If distance between circle center and box projected collison point is less than circle radius , then colliding.
		if((circleLocalPos - collisionPointProject).Length() < ASphereShape->GetRadius())
		{
			//make collsiion info 
			pRigidBody::CollisionInfo objCollisionInfo;
			objCollisionInfo.CollidedWith = bRigidBody;
			objCollisionInfo.ImpactPoint = spVector3(collisionPointProject.x, collisionPointProject.y,0);

			aRigidBody->CollisionOccured(objCollisionInfo);

			if (Drawhelper != nullptr)
			{
				SDL_Color Colour;
				Colour.r = 255;
				Drawhelper->Draw2DSphere(boxCenterPos - collisionPointProject, 10.0f, Colour, 10, 5.0f);
			}

			spVector3 direction =  spVector3(circleLocalPos.x, circleLocalPos.y, 0) - spVector3(collisionPointProject.x, collisionPointProject.y, 0);
			spVector3 normal = direction.Normalize();
			//update velocities based on collision

			_info->ImpactNormal = normal;
			_info->CollidedWith = bRigidBody;
			ResolveCollision(aRigidBody, bRigidBody, normal);

			return true;
		}
		else
		{
			return false;
		}
}

bool PhysicsWorld::AABBtoAABB( class pRigidBody *a,  class pRigidBody *b, pRigidBody::CollisionInfo * _info)
{
	if (a != nullptr || b != nullptr)
	{
		pShapeBox *A = (pShapeBox*)a->GetShape();
		pShapeBox *B = (pShapeBox*)b->GetShape();

		spVector3 aPos = a->GetPosition();
		spVector3 bPos = b->GetPosition();

		spVector3 aMinExtentsPos = aPos + A->m_min;
		spVector3 aMaxExtentsPos = aPos + A->m_max;

		spVector3 bMinExtentsPos = bPos + B->m_min;
		spVector3 bMaxExtentsPos = bPos + B->m_max;

		//collision cant occur if box is outside of another box bounds on 1 axis
		if (aMaxExtentsPos.x < bMinExtentsPos.x || aMinExtentsPos.x > bMaxExtentsPos.x)
		{
			return false;
		}
		if (aMaxExtentsPos.y < bMinExtentsPos.y || aMinExtentsPos.y > bMaxExtentsPos.y)
		{
			return false;
		}

		

		spVector3 direction = b->GetPosition() - a->GetPosition();
		spVector3 normal = direction.Normalize();
		_info->ImpactNormal = normal;
		_info->CollidedWith = b;
		//update velocities based on collision
		ResolveCollision(a, b, normal);
		return true;
	}
	return false;

}

bool PhysicsWorld::AABBtoCircle( class pRigidBody *a,  class  pRigidBody *b, pRigidBody::CollisionInfo * _info)
{
	return CircletoAABB(b, a, _info);
}

void PhysicsWorld::ResolveCollision(pRigidBody *a, pRigidBody *b, spVector3 _normal)
{
	// Calculate relative velocity
	spVector3 rv = b->GetVelocity() - a->GetVelocity();

	// Calculate relative velocity in terms of the normal direction
	float velAlongNormal = Dot(rv, _normal);

	// Do not resolve collision if objcects are moving away from each other.
	if (velAlongNormal < 0)
	{

		// Get smallest restitution
		float e = Min(a->GetRestitution(), a->GetRestitution());

		// Calculate impulse scalar
		float j = -(1 + e) * velAlongNormal;
		j /= 1 / a->m_Mass + 1 / b->m_Mass;

		// Apply impulse
		spVector3 impulse = j * _normal;

		if (a->m_ObjectType != pRigidBody::COLLISION_OBJECT)
		{
			a->m_LinearVelocity = a->m_LinearVelocity - a->GetMassInverse() * impulse;
		}

		if (b->m_ObjectType != pRigidBody::COLLISION_OBJECT)
		{
			b->m_LinearVelocity = b->m_LinearVelocity + b->GetMassInverse() * impulse;
		}
	}
}

void PhysicsWorld::EulerStep(float _deltaTick, pRigidBody * _rigidBody)
{
	spVector3 newPos = _rigidBody->m_LinearVelocity * _deltaTick;
	_rigidBody->m_Position = _rigidBody->m_Position + newPos;

	spVector3 newVel  = (_rigidBody->GetMassInverse() * _rigidBody->m_Force) * _deltaTick;
	_rigidBody->m_LinearVelocity = _rigidBody->m_LinearVelocity + newVel;
}

pRigidBody* PhysicsWorld::CreateRigidBody(float _mass, spVector3 _position, pShape* _Shape, class GameObject * _Owner)
{
	pRigidBody::RigidBodyConstructorInfo RigidBodyInfo(_mass, _position, _Shape, _Owner);
	pRigidBody * newRigidBody = new pRigidBody(RigidBodyInfo);

	m_RigidBodyList.push_back(newRigidBody);

	return newRigidBody;
}

void PhysicsWorld::AddRigidBody(pRigidBody* _rb)
{
	if (_rb != nullptr)
	{
		m_RigidBodyList.push_back(_rb);
	}
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
				_ColInfo->ImpactNormal = spVector3(0, 0, 0);
				if((this->*m_CollisionCheckArray[obj1->GetShape()->GetShapeType()][obj2->GetShape()->GetShapeType()])(obj1, obj2, _ColInfo))
				{
					spVector3 normal = _ColInfo->ImpactNormal;

					obj1->CollisionStateChanged(true);
					//obj1->CollisionOccured();
				}
			}
		}
	}
}