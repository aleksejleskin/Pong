#include <iostream>
#include <string>
#include "SDL.h"
#include "Game.h"
#include <SDL_ttf.h>


int main(int, char**)
{

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Extra Pong", 100, 100, 1280, 1024, SDL_WINDOW_SHOWN);
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
	
	SDL_Event *SDLevent = new SDL_Event();
	// Timing variables
	Uint32 old_time = 0, current_time = 0;
	float ftime = 0.0f;

	bool m_allowUpdate = true;

	bool quit = false;





	while (quit != true)
	{
		m_allowUpdate = true;
		if (SDLevent->type == SDL_WINDOWEVENT)
		{
			if (SDLevent->window.type == (SDL_WINDOWEVENT_MOVED || SDL_WINDOWEVENT_RESIZED))
			{
				m_allowUpdate = false;
			}
		}

if (m_allowUpdate)
		{
		old_time = current_time;
		current_time = SDL_GetTicks();
		ftime = (current_time - old_time) / 1000.0f;

		// Check for messages
		if (SDL_PollEvent(SDLevent))
		{
			// Check for the quit message
			if (SDLevent->type == SDL_QUIT)
			{
				std::cout << "QUIT" << std::endl;
				// Quit the program
				break;
			}
		}



			GameModeSimple->Update(ftime, SDLevent);
			GameModeSimple->Render(ren);
		}
	}


	//std::cout << "Resource path is: " << getResourcePath() << std::endl;

	//SDL_DestroyTexture(tex);
	//SDL_DestroyRenderer(ren);
	//SDL_DestroyWindow(win);
	//SDL_Quit();
	return 0;
}