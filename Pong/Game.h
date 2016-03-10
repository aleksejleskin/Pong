#pragma once
#include "Math.h"
#include <string>
#include "SDL.h"

using namespace Math;
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
};