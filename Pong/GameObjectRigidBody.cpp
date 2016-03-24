#include "GameObjectRigidBody.h"
#include <iostream>


GameObjectRigidBody::GameObjectRigidBody(const GORigidBodyConstructor & _parameters)
{
	ConstructGameObject(_parameters);
}

GameObjectRigidBody::GameObjectRigidBody(const float & _mass, const class spVector3 & _position, class pShape* _CollisionShape, struct SDL_Texture *_texture, class PhysicsWorld * _physics, class DrawHelper* _debugDraw, TextManager *_textManger)
{
	GORigidBodyConstructor paramaters = GORigidBodyConstructor(_mass, _position, _CollisionShape, _texture, _physics, _debugDraw, _textManger);
	ConstructGameObject(paramaters);
}


GameObjectRigidBody::~GameObjectRigidBody()
{

}

void GameObjectRigidBody::ConstructGameObject(const GORigidBodyConstructor &_parameters)
{
	//m_PhysicsWorld->AddRigidBody(this);
	//GoRigidBody Specific
	m_TextManager = _parameters.textManger;
	m_PhysicsWorld = _parameters.physics;
	m_DebugDrawHelper = _parameters.debugDraw;
	m_SurfaceTexture = _parameters.texture;
	m_Scale = spVector3(1.0f, 1.0f, 1.0f);
	m_Rotation = 0.0f;
	m_Position = _parameters.position;

	if (m_SurfaceTexture != nullptr)
	{
		int h, w;
		SDL_QueryTexture(m_SurfaceTexture, NULL, NULL, &w, &h);
		m_TextureSize = spVector2(h,w);
	}
	else
	{
		m_TextureSize = spVector2();
	}
}

void GameObjectRigidBody::Update(float _deltaTime, SDL_Event * sdlEvent)
{
	if (m_RigidBody != nullptr)
	{
		m_Position = m_RigidBody->GetPosition();
	}
}

void GameObjectRigidBody::Render(SDL_Renderer * _renderer)
{
	if (_renderer != nullptr)
	{
		//SDL_SetColorKey(m_SurfaceTexture, SDL_SRCCOLORKEY, colorkey);

		if (m_RigidBody->GetShape() != nullptr)
		{
			m_RigidBody->GetShape()->DrawShape(_renderer, m_DebugDrawHelper, spVector2(m_Position.x, m_Position.y));
		}

		if (m_SurfaceTexture != nullptr)
		{
			spVector2 pos = spVector2(m_Position.x - m_TextureSize.x * m_Scale.x / 2, m_Position.y - m_TextureSize.y * m_Scale.y / 2);
			SDL_Rect rect = MakeSDLRect(pos, m_TextureSize.y * m_Scale.y, m_TextureSize.x * m_Scale.x);
			SDL_RenderCopyEx(_renderer, m_SurfaceTexture, NULL, &rect, m_Rotation, NULL, SDL_RendererFlip::SDL_FLIP_NONE);
		}
	}
}

void GameObjectRigidBody::SetTextureSize(const spVector2 &_newSize)
{
	m_TextureSize = _newSize;
}

void GameObjectRigidBody::SetScale(spVector3 &_vNewScale)
{
	m_Scale = _vNewScale;
}
