#pragma once

#include "pShape.h"
#include "pRigidBody.h"
#include <vector>
#include "Math.h"
#include "DrawHelper.h"

class PhysicsWorld
{
public:
	PhysicsWorld();

	~PhysicsWorld();

	typedef bool(PhysicsWorld::* CollisionCheck)(class pRigidBody *a, class pRigidBody *b, pRigidBody::CollisionInfo * _info);

	bool AABBtoCircle(class pRigidBody *a, class pRigidBody *b, pRigidBody::CollisionInfo * _info);
	bool CircletoAABB(class pRigidBody *a, class pRigidBody *b, pRigidBody::CollisionInfo * _info);

	bool CircletoCircle(class pRigidBody *a, class pRigidBody *b, pRigidBody::CollisionInfo * _info);
	bool AABBtoAABB(class pRigidBody *a, class pRigidBody *b, pRigidBody::CollisionInfo * _info);

	void stepSimulation(float _dt);


	CollisionCheck m_CollisionCheckArray[2][2];
	void ResolveCollision(class pRigidBody *a, class pRigidBody *b, spVector3 _normal);

	pRigidBody * CreateRigidBody(float _mass, spVector3 _position, class pShape* _Shape, class GameObject * _Owner);
	void AddRigidBody(class pRigidBody* _rb);

	std::vector<pRigidBody*> m_RigidBodyList;

	//Intigrations
	void EulerStep(float _deltaTick, class pRigidBody * _rigidBody);

	DrawHelper * Drawhelper;

	struct pRigidBody::CollisionInfo * _ColInfo;
};

