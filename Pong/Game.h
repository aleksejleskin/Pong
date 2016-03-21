#pragma once
#include "aMath.h"
#include <string>
#include "SDL.h"
#include "GameObjectRigidBody.h"
#include <vector>

using namespace aMath;
using namespace std;

class Game
{
public:
	Game(void);
	Game(SDL_Renderer *_ren);
	~Game(void);

	void Update(float _deltaTick);
	void Render(SDL_Renderer *_ren);


protected:
	SDL_Renderer * sdl_Renderer;
	vector<GameObjectRigidBody*> GameObjectList;
	PhysicsWorld* m_Physics = new PhysicsWorld();
	DrawHelper* m_DrawDebug = new DrawHelper();
};