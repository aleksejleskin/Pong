#pragma once
#include "aMath.h"
#include <string>
#include "SDL.h"
#include "GameObjectRigidBody.h"
#include <vector>
#include "TextManager.h"
#include "PongBall.h"

using namespace aMath;
using namespace std;

class Game
{
public:
	Game(void);
	Game(SDL_Renderer *_ren);
	~Game(void);

	void Update(float _deltaTick, SDL_Event *SDLevent);
	void Render(SDL_Renderer *_ren);

	void CreateBorders(spVector2 &_size, SDL_Texture &_texture);
protected:

	SDL_Renderer * sdl_Renderer;
	vector<GameObjectRigidBody*> GameObjectList;
	PhysicsWorld* m_Physics;
	DrawHelper* m_DrawDebug;
	TextManager *m_TextManager;

	//HACk
	PongBall * m_PongBall;
};