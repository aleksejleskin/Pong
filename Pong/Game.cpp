#include "Game.h"
#include "res_path.h"
#include "PhysicsWorld.h"
#include "pShapeSphere.h"
#include "pShapeBox.h"
#include "DrawHelper.h"
#include "spScalar.h"

#include "PlayerPaddle.h"
#include "PongBall.h"

Game::Game(void)
{

}

Game::Game(SDL_Renderer *_ren)
{

	pShape* shapeSphere = new pShapeSphere(100.0f);
	pShape* shapeBox = new pShapeBox(spVector3(-100, -100, 0), spVector3(100, 100, 0));


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
			GameObjectRigidBody::GORigidBodyConstructor paramaters = GameObjectRigidBody::GORigidBodyConstructor(1000000.0f, spVector3(800, 1024/2, 0), shapeBox, tex, m_Physics, m_DrawDebug);
			PlayerPaddle * obj = new PlayerPaddle(paramaters);
			m_Physics->AddRigidBody(obj);
			obj->GetShape()->SetShapeDebugDraw(true);
			//obj->ApplyImpulse(spVector3(-200, 0, 0));
			GameObjectList.push_back(obj);

			paramaters = GameObjectRigidBody::GORigidBodyConstructor(1000000.0f, spVector3(200, 1024 / 2, 0), shapeBox, tex, m_Physics, m_DrawDebug);
			obj = new PlayerPaddle(paramaters);
			m_Physics->AddRigidBody(obj);
			obj->GetShape()->SetShapeDebugDraw(true);
			//obj->ApplyImpulse(spVector3(-200, 0, 0));
			GameObjectList.push_back(obj);
		}
	}

	imagePath = getResourcePath("Images") + "PongBall.bmp";
	bmp = SDL_LoadBMP(imagePath.c_str());

	if (bmp == nullptr)
	{
		std::cout << SDL_GetError();
	}
	SDL_SetColorKey(bmp, SDL_TRUE, SDL_MapRGB(bmp->format, 255, 0, 255));

	tex = SDL_CreateTextureFromSurface(_ren, bmp);
	//
	
	if (tex != nullptr)
	{
		{
			GameObjectRigidBody::GORigidBodyConstructor paramaters = GameObjectRigidBody::GORigidBodyConstructor(10.0f, spVector3(250, 1024 / 2, 0), shapeSphere, tex, m_Physics, m_DrawDebug);
			PongBall * obj = new PongBall(paramaters);
			m_Physics->AddRigidBody(obj);
			obj->GetShape()->SetShapeDebugDraw(true);
			obj->ApplyImpulse(spVector3(1000, 0, 0));
			GameObjectList.push_back(obj);
		}
	}


	SDL_FreeSurface(bmp);
}


Game::~Game(void)
{
	delete m_Physics;
	delete m_DrawDebug;

	for each (GameObjectRigidBody *obj in GameObjectList)
	{
		if (obj != nullptr)
		{
			delete(obj);
		}
	}
	GameObjectList.clear();
}

void Game::Update(float _deltaTick)
{
	//Update physics, all rigidbodies
	m_Physics->stepSimulation(_deltaTick);

	//update all objects
	for each (GameObjectRigidBody *GameObject in GameObjectList)
	{
		GameObject->Update(_deltaTick);
	}



	m_DrawDebug->Update(_deltaTick);


}

void Game::Render(SDL_Renderer *_ren)
{
	//Backgroudn Colour
	SDL_SetRenderDrawColor(_ren, 180, 207, 236, 255);
	//Clear the screen before drawing new frame
	SDL_RenderClear(_ren);


	//Loop though all Gameobjects and draw them.
	for each (GameObjectRigidBody *GameObject in GameObjectList)
	{
		GameObject->Render(_ren);
	}

	SDL_SetRenderDrawColor(_ren, 0, 0, 0, 0);

	m_DrawDebug->Render(_ren);

	//Draw This Frame to Screen
	SDL_RenderPresent(_ren);
}
