#include <iostream>
#include <string>
#include "SDL.h"
#include "Game.h"



int main(int, char**)
{

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr){
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	Game * GameModeSimple;
	GameModeSimple = new Game(ren);
	
	SDL_Event event;
	// Timing variables
	Uint32 old_time = 0, current_time = 0;
	float ftime = 0.0f;


	while (GameModeSimple != nullptr)
	{
		old_time = current_time;
		current_time = SDL_GetTicks();
		ftime = (current_time - old_time) / 1000.0f;

		// Check for messages
		if (SDL_PollEvent(&event))
		{
			// Check for the quit message
			if (event.type == SDL_QUIT)
			{
				// Quit the program
				break;
			}
		}

		GameModeSimple->Update(ftime);
		GameModeSimple->Render(ren);
	}


	//std::cout << "Resource path is: " << getResourcePath() << std::endl;

	//SDL_DestroyTexture(tex);
	//SDL_DestroyRenderer(ren);
	//SDL_DestroyWindow(win);
	//SDL_Quit();
	return 0;
}