#pragma once
#include "spVector3.h"
#include "PhysicsWorld.h"
#include "pShape.h"
#include "DrawHelper.h"
#include "SDL.h"

class GameObjectRigidBody : public pRigidBody
{
public:

	struct GORigidBodyConstructor
	{
		float mass;
		spVector3 position;
		pShape *CollisionShape;
		PhysicsWorld *physics;
		DrawHelper *debugDraw;
		SDL_Texture *texture;

		GORigidBodyConstructor(const float & _mass, const class spVector3 & _position, pShape* _CollisionShape, SDL_Texture *_texture, PhysicsWorld * _physics, DrawHelper* _debugDraw)
		{
			mass = _mass;
			position = _position;
			CollisionShape = _CollisionShape;
			physics = _physics;
			debugDraw = _debugDraw;
			texture = _texture;
		}
	};

	GameObjectRigidBody(const float & _mass, const class spVector3 & _position, pShape* _CollisionShape, SDL_Texture *_texture, PhysicsWorld * _physics, DrawHelper* _debugDraw);
	GameObjectRigidBody(const GORigidBodyConstructor & _parameters);

	~GameObjectRigidBody();

	virtual void Update(float _deltaTime);
	virtual void Render(SDL_Renderer * _renderer);

protected:
	void ConstructGameObject(const GORigidBodyConstructor &parameters);

	PhysicsWorld *m_PhysicsWorld;
	DrawHelper *m_DebugDrawHelper;
	SDL_Texture *m_SurfaceTexture;
};

