#pragma once
#include "Math.h"
#include <string>
#include "SDL.h"

using namespace Math;
using namespace std;

class Object
{
public:
	Object(void);
	~Object(void);


	void			SetPosition(Vector2 _pos);
	void			SetRotation(float _rot);

	Vector2			GetPostion();
	float			GetRotation();

	virtual void	Update(float _deltaTick);
	virtual void	Render(SDL_Renderer *_ren);
	bool			SetTexture(SDL_Texture *_texture);
	void			SetRectSize(Vector2 _size);
	void			SetScale(Vector2 _scale);

protected:
	SDL_Texture *	m_Texture;

	Vector2			m_Rect;
	Vector2			m_Position;
	Vector2			m_Scale;
	float			m_Rotation;
};

