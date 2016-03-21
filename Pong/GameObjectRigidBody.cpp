#include "GameObjectRigidBody.h"



GameObjectRigidBody::GameObjectRigidBody(const GORigidBodyConstructor & _parameters) : pRigidBody(_parameters.mass, _parameters.position, _parameters.CollisionShape)
//pRigidBody(_parameters.mass, _parameters.position, _parameters.CollisionShape)
{
	ConstructGameObject(_parameters);
}

GameObjectRigidBody::GameObjectRigidBody(const float & _mass, const class spVector3 & _position, pShape* _CollisionShape, SDL_Texture *_texture, PhysicsWorld * _physics, DrawHelper* _debugDraw) : pRigidBody(_mass, _position, _CollisionShape)
{
	GORigidBodyConstructor paramaters = GORigidBodyConstructor(_mass, _position, _CollisionShape, _texture, _physics, _debugDraw);
	ConstructGameObject(paramaters);
}


GameObjectRigidBody::~GameObjectRigidBody()
{

}

void GameObjectRigidBody::ConstructGameObject(const GORigidBodyConstructor &_parameters)
{
	//m_PhysicsWorld->AddRigidBody(this);
	//GoRigidBody Specific
	m_PhysicsWorld = _parameters.physics;
	m_DebugDrawHelper = _parameters.debugDraw;
	m_SurfaceTexture = _parameters.texture;
}

void GameObjectRigidBody::Update(float _deltaTime)
{

}

void GameObjectRigidBody::Render(SDL_Renderer * _renderer)
{
	if (_renderer != nullptr)
	{
		//SDL_SetColorKey(m_SurfaceTexture, SDL_SRCCOLORKEY, colorkey);

		if (m_CollisionShape != nullptr)
		{
			m_CollisionShape->DrawShape(_renderer, m_DebugDrawHelper, spVector2(m_Postion.x, m_Postion.y));
		}

		if (m_SurfaceTexture != nullptr)
		{
			int h, w;
			SDL_QueryTexture(m_SurfaceTexture, NULL, NULL, &w,&h);

			spVector2 pos = spVector2(m_Postion.x - w / 2, m_Postion.y - h / 2);
			SDL_Rect rect = MakeSDLRect(pos, h, w);
			SDL_RenderCopy(_renderer, m_SurfaceTexture, NULL, &rect);



		}
	}
}