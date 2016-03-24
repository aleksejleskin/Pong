#pragma once

#include "GameObject.h"
#include "spVector3.h"
#include "spVector2.h"
#include "PhysicsWorld.h"
#include "pShape.h"
#include "DrawHelper.h"
#include "SDL.h"
#include "TextManager.h"

class GameObjectRigidBody : public GameObject
{
public:

	struct GORigidBodyConstructor
	{
		float mass;
		spVector3 position;
		class pShape *CollisionShape;
		class PhysicsWorld *physics;
		DrawHelper *debugDraw;
		SDL_Texture *texture;
		TextManager *textManger;

		GORigidBodyConstructor(const float & _mass, const class spVector3 & _position, class pShape* _CollisionShape, SDL_Texture *_texture, class PhysicsWorld * _physics, DrawHelper* _debugDraw, TextManager *_textManger)
		{
			mass = _mass;
			position = _position;
			CollisionShape = _CollisionShape;
			physics = _physics;
			debugDraw = _debugDraw;
			texture = _texture;
			textManger = _textManger;
		}
	};

	GameObjectRigidBody(const float & _mass, const class spVector3 & _position, class pShape* _CollisionShape, struct SDL_Texture *_texture, class PhysicsWorld * _physics, DrawHelper* _debugDraw, TextManager *_textManger);
	GameObjectRigidBody(const GORigidBodyConstructor & _parameters);

	~GameObjectRigidBody();

	void SetTextureSize(const spVector2 &_vNewSize);
	void SetScale(spVector3 &_vNewScale);

	virtual void Update(float _deltaTime, SDL_Event * sdlEvent);
	virtual void Render(SDL_Renderer * _renderer);


	void ConstructGameObject(const GORigidBodyConstructor &parameters);

	TextManager *m_TextManager;
	class PhysicsWorld *m_PhysicsWorld;
	DrawHelper *m_DebugDrawHelper;
	SDL_Texture *m_SurfaceTexture;
	spVector2 m_TextureSize;

	class pRigidBody *m_RigidBody;

	spVector3 m_Position;
	spVector3 m_Scale;
	double		m_Rotation;
};

