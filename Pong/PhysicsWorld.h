#pragma once

#include "pShape.h"

#include "pRigidBody.h"
#include <vector>
#include "Math.h"



class PhysicsWorld
{
public:
	PhysicsWorld();

	~PhysicsWorld();

	typedef bool(PhysicsWorld::* CollisionCheck)(class pRigidBody *a, class pRigidBody *b);

	bool AABBtoCircle(class pRigidBody *a, class pRigidBody *b);
	bool CircletoAABB(class pRigidBody *a, class pRigidBody *b);

	bool CircletoCircle(class pRigidBody *a, class pRigidBody *b);
	bool AABBtoAABB(class pRigidBody *a, class pRigidBody *b);

	void stepSimulation(float _dt);


	CollisionCheck m_CollisionCheckArray[2][2];
	void ResolveCollision(class pRigidBody *a, class pRigidBody *b, spVector3 _normal);

	pRigidBody * CreateRigidBody(float _mass, spVector3 _position, class pShape* _Shape);
	void AddRigidBody(pRigidBody* _rb);

	std::vector<pRigidBody*> m_RigidBodyList;

	//Intigrations
	void EulerStep(float _deltaTick, class pRigidBody * _rigidBody);

};

