#pragma once
#include "aMath.h"
#include <string>
#include "SDL.h"

using namespace aMath;
using namespace std;

class Object
{
public:
	Object(void);
	~Object(void);


	void			SetPosition(spVector2 _pos);
	void			SetRotation(float _rot);

	spVector2			GetPostion();
	float			GetRotation();

	virtual void	Update(float _deltaTick);
	virtual void	Render(SDL_Renderer *_ren);
	bool			SetTexture(SDL_Texture *_texture);
	void			SetRectSize(spVector2 _size);
	void			SetScale(spVector2 _scale);

protected:
	SDL_Texture *	m_Texture;

	spVector2			m_Rect;
	spVector2			m_Position;
	spVector2			m_Scale;
	float			m_Rotation;
};

