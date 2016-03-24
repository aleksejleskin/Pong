#pragma once
#include "pShape.h"
#include "pGlobal.h"
#include "aMath.h"
#include "GameObject.h"

using namespace aMath;
//
//collision Callback Delegate
class pRigidBody
{
public:

	struct CollisionInfo
	{
		spVector3 ImpactPoint;
		spVector3 ImpactNormal;
		class pRigidBody * CollidedWith;
	};

	enum CollisionObjectType
	{
		COLLISION_OBJECT,
		RIGID_BODY
	};

	struct RigidBodyConstructorInfo
	{
		float mass;
		spVector3 position;
		class pShape* collisionShape;
		class GameObject *Owner;

		RigidBodyConstructorInfo(float _mass, spVector3 _position, pShape* _shape, class GameObject *_owner)
		{
			mass = _mass;
			position = _position;
			collisionShape = _shape;
			Owner = _owner;
		}
	};

	pRigidBody(float _mass, spVector3 _position, pShape* _CollisionShape, class GameObject *_owner);
	pRigidBody(const RigidBodyConstructorInfo _RigidBodyInfo);
	~pRigidBody();


	//CollisionCallBack
	virtual void CollisionOccured(struct CollisionInfo &_info);

	void ApplyImpulse(const spVector3 _forceDirection);

	void CalculateInverseMass();
	void SetMass(float _newMass);
	float GetMass();
	float GetMassInverse();

	pShape* GetShape();
	spVector3 GetPosition();

	void SetObjectType(CollisionObjectType & _newType);

	void SetPosition(spVector3 _newPos);
	spVector3 GetVelocity();
	float GetRestitution();

	void SetUpRigidBody(const RigidBodyConstructorInfo _RigidBodyInfo);

	//collision check
	void CollisionStateChanged(bool _isColliding);
	bool m_isColliding;

	void SetScale(spVector3 & _newScale);
	spVector3 GetScale();

	pShape*		m_CollisionShape;
	spVector3	m_Position;
	spVector3	m_Scale;
	spVector3	m_Rotation;

	float	m_Mass;
	spVector3 m_LinearVelocity;
	float	m_Restitution;
	spVector3 m_Force;
	float	m_InverseMass;

	CollisionObjectType m_ObjectType;

	//HACK
	CollisionInfo m_CurrentCollision;
	GameObject* m_Owner;
};

