#include "Game.h"
#include "Object.h"
#include "RigidBodyObject.h"
#include <vector>
#include "res_path.h"
#include "PhysicsWorld.h"
#include "pShapeSphere.h"

vector<Object*> ObjectList;
std::vector<Object*>current_obj;
std::vector<Object*>::iterator iter, endList;
PhysicsWorld* m_Physics = new PhysicsWorld();

Game::Game(void)
{

}

Game::Game(SDL_Renderer *_ren)
{
	float out = aPow(2, 2);

	pShape* shape = new pShapeSphere(8.0f);
	m_Physics->CreateRigidBody(1.0f, Vector3(250, 250, 0), shape);
	m_Physics->CreateRigidBody(1.0f, Vector3(250, 250, 0), shape);


	//RigidBodyCircle * GameObjectTest =  new RigidBodyCircle();
//	GameObjectTest->SetMass(10.0f);
//	GameObjectTest->AddForce(Vector2(100.0f, 0.0f), RigidBodyObject::ForceMode::IMPULSE);
	//m_Physics->AddRigidBody(GameObjectTest);
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
		//if(GameObjectTest->SetTexture(tex))
		{
		//	ObjectList.push_back(GameObjectTest);
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
	m_Physics->stepSimulation();
}

void Game::Render(SDL_Renderer *_ren)
{
	SDL_SetRenderDrawColor(_ren, 255, 0, 0, 255);
	SDL_RenderClear(_ren);

	//Loop Objects
	for(iter = ObjectList.begin(), endList = ObjectList.end() ; iter != endList; ++iter) 
	{
		(*iter)->Render(_ren);
	}

	SDL_SetRenderDrawColor(_ren, 0, 0, 0, 0);

	for each(pRigidBody* obj in m_Physics->m_RigidBodyList)
	{
		SDL_Rect rect;
		rect.h = 40;
		rect.w = 40;
		rect.x = obj->GetPosition().x;
		rect.y = obj->GetPosition().y;
		//SDL_RenderFillRect(_ren, &rect);
		SDL_RenderDrawRects(_ren, &rect,1);
	}
	
	SDL_RenderPresent(_ren);

	
	

}
