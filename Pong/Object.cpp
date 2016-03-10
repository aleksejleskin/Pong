#include "Object.h"
#include <iostream>

using namespace std;
Object::Object(void)
{
	m_Scale = Vector2(0.0f,0.0f);
	m_Rect = Vector2(0.0f,0.0f);
	m_Position = Vector2(0.0f, 0.0f);
	m_Rotation = 0.0f;
}

Object::~Object(void)
{

}

void Object::Update(float _deltaTick)
{
	//cout<< "update" << endl;
}

void Object::Render(SDL_Renderer *_ren)
{
	if(_ren != nullptr)
	{
		if(m_Texture != nullptr)
		{
			SDL_RenderCopy(_ren, m_Texture, NULL, &MakeSDLRect(m_Position, 100.0f,100.0f));
		}
	}
}

void Object::SetRectSize(Vector2 _size)
{
	m_Rect = _size;
}

bool Object::SetTexture(SDL_Texture *_texture)
{
	if (_texture == nullptr)
	{
		return false;
	}

	//assign new texture
	m_Texture =_texture;

	if (m_Texture == nullptr)
	{
		return false;
	}

	return true;
}

void Object::SetPosition(Vector2 _pos)
{
	m_Position = _pos;
}

void Object::SetRotation(float _rot)
{
	m_Rotation = _rot;
}

Vector2 Object::GetPostion()
{
	return m_Position;
}

float Object::GetRotation()
{
	return m_Rotation;
}
