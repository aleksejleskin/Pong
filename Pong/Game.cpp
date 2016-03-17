#include "Game.h"
#include "Object.h"
#include "RigidBodyObject.h"
#include <vector>
#include "res_path.h"
#include "PhysicsWorld.h"
#include "pShapeSphere.h"
#include "DrawHelper.h"

vector<Object*> ObjectList;
std::vector<Object*>current_obj;
std::vector<Object*>::iterator iter, endList;
PhysicsWorld* m_Physics = new PhysicsWorld();
DrawHelper* m_DrawDebug = new DrawHelper();

Game::Game(void)
{

}

Game::Game(SDL_Renderer *_ren)
{
	float out = aPow(2, 2);
	spVector3 vec1 = spVector3(0, 0, 0);
	vec1 = spVector3(0, 0, 0);
	vec1 += vec1 + vec1;

	pShape* shape = new pShapeSphere(80.0f);
	pRigidBody* body1 =  m_Physics->CreateRigidBody(10.0f, Vector3(250, 100, 0), shape);
	body1->m_Mass = 20.0f;
	body1->ApplyImpulse(Vector3(600, 0, 0));
	pRigidBody* body2 = m_Physics->CreateRigidBody(10.0f, Vector3(500, 50, 0), shape);
	body2->m_Mass = 2.0f;
	//body2->ApplyImpulse(Vector3(1, 0, 0));

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
	m_Physics->stepSimulation(_deltaTick);
	m_DrawDebug->Update(_deltaTick);

	for each(pRigidBody* obj in m_Physics->m_RigidBodyList)
	{

		SDL_Colour colour;
		colour.r = 255;
		colour.g = 0;
		colour.b = 0;
		colour.a = 0;

		Vector2 drawPos;
		drawPos.x = obj->GetPosition().x;
		drawPos.y = obj->GetPosition().y;

		bool isColliding = obj->m_isColliding;

		SDL_Colour SphereColour;
		SphereColour.r = isColliding ? 0 : 255;
		SphereColour.g = isColliding ? 255 : 0;
		SphereColour.b = 0;
		SphereColour.a = 0;

		m_DrawDebug->Draw2DSphere(drawPos, 80, SphereColour, 16, 1.0f);
	}
}

void Game::Render(SDL_Renderer *_ren)
{
	SDL_SetRenderDrawColor(_ren, 180, 207, 236, 255);
	SDL_RenderClear(_ren);

	//Loop Objects
	for(iter = ObjectList.begin(), endList = ObjectList.end() ; iter != endList; ++iter) 
	{
		(*iter)->Render(_ren);
	}

	SDL_SetRenderDrawColor(_ren, 0, 0, 0, 0);

	m_DrawDebug->Render(_ren);
	for each(pRigidBody* obj in m_Physics->m_RigidBodyList)
	{
	

		m_DrawDebug->Render(_ren);
		
	}
	
	SDL_RenderPresent(_ren);

	
	

}
