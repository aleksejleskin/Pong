#include "Game.h"
#include "Object.h"
#include "RigidBodyObject.h"
#include <vector>
#include "res_path.h"

vector<Object*> ObjectList;
std::vector<Object*>current_obj;
std::vector<Object*>::iterator iter, endList;

Game::Game(void)
{

}

Game::Game(SDL_Renderer *_ren)
{

	RigidBodyObject * GameObjectTest =  new RigidBodyObject();
	GameObjectTest->SetMass(10.0f);
	GameObjectTest->AddForce(Vector2(100.0f,0.0f));
	//Find texture
	std::string imagePath = getResourcePath("Images") + "hello.bmp";
	SDL_Surface* bmp = SDL_LoadBMP(imagePath.c_str());

	if(bmp == nullptr)
	{
		std::cout << SDL_GetError();
	}


	SDL_Texture *tex = SDL_CreateTextureFromSurface(_ren, bmp);
	//

	if(tex	!= nullptr)
	{
		//Assign Texture
		if(GameObjectTest->SetTexture(tex))
		{
			ObjectList.push_back(GameObjectTest);
		}
	}
	SDL_FreeSurface(bmp);
}


Game::~Game(void)
{

}

void Game::Update(float _deltaTick)
{
	//update all objects
	for(iter = ObjectList.begin(), endList = ObjectList.end() ; iter != endList; ++iter) 
	{
		(*iter)->Update(_deltaTick);
	}
}

void Game::Render(SDL_Renderer *_ren)
{
	SDL_RenderClear(_ren);

	//Loop Objects
	for(iter = ObjectList.begin(), endList = ObjectList.end() ; iter != endList; ++iter) 
	{
		(*iter)->Render(_ren);
	}

	SDL_RenderPresent(_ren);
}
