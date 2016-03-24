#include "Game.h"
#include "res_path.h"
#include "PhysicsWorld.h"
#include "pShapeSphere.h"
#include "pShapeBox.h"
#include "DrawHelper.h"
#include "spScalar.h"
#include "Wall.h"
#include "PlayerPaddle.h"
#include "PongBall.h"
#include "Text.h"
#include <string>
#include "HelperFunctions.h"

using namespace std;

#define DEBUG_DRAW true

PlayerPaddle * player1, *player2;

Game::Game(void)
{
}

Game::Game(SDL_Renderer *_ren)
{
	m_TextManager = new TextManager();
	m_Physics = new PhysicsWorld();
	m_DrawDebug = new DrawHelper();
	m_Physics->Drawhelper = m_DrawDebug;

	pShape* shapeSphere = new pShapeSphere(50.0f);
	pShape* shapeBox = new pShapeBox(spVector3(10, 50, 0));


	std::string imagePath = getResourcePath("Images") + "hello.bmp";
	SDL_Surface* bmp = SDL_LoadBMP(imagePath.c_str());

	if (bmp == nullptr)
	{
		std::cout << SDL_GetError();
	}


	SDL_Texture *tex = SDL_CreateTextureFromSurface(_ren, bmp);
	//

	if (tex != nullptr)
	{
		//Assign Texture
		//if(GameObjectTest->SetTexture(tex))
		{
			GameObjectRigidBody::GORigidBodyConstructor paramaters = GameObjectRigidBody::GORigidBodyConstructor(10000.0f, spVector3(1000, 200, 0), shapeBox, tex, m_Physics, m_DrawDebug, m_TextManager);
			player1 = new PlayerPaddle(paramaters);
			player1->m_TextManager = m_TextManager;
			player1->SetTextureSize(spVector2(20, 100));
			GameObjectList.push_back(player1);
			player1->m_ScoreTextComponent->SetText(to_string(player1->GetScore()));

			paramaters = GameObjectRigidBody::GORigidBodyConstructor(10000.0f, spVector3(500, 200, 0), shapeBox, tex, m_Physics, m_DrawDebug, m_TextManager);
			player2 = new PlayerPaddle(paramaters);
			player2->m_TextManager = m_TextManager;
			player2->SetTextureSize(spVector2(20, 100));
			GameObjectList.push_back(player2);
			player2->m_ScoreTextComponent->SetText(to_string(player2->GetScore()));
		}
	}


	CreateBorders(spVector2(800, 800), *tex);


	imagePath = getResourcePath("Images") + "PongBall.bmp";
	bmp = SDL_LoadBMP(imagePath.c_str());

	if (bmp == nullptr)
	{
		std::cout << SDL_GetError();
	}
	SDL_SetColorKey(bmp, SDL_TRUE, SDL_MapRGB(bmp->format, 255, 0, 255));

	tex = SDL_CreateTextureFromSurface(_ren, bmp);

	if (tex != nullptr)
	{
		{
			GameObjectRigidBody::GORigidBodyConstructor paramaters = GameObjectRigidBody::GORigidBodyConstructor(10.0f, spVector3(500, 700, 0), shapeSphere, tex, m_Physics, m_DrawDebug, m_TextManager);
			m_PongBall = new PongBall(paramaters);
			m_PongBall->SetScale(spVector3(.5f, .5f, .5f));
			//GameObjectList.push_back(obj);
		}
	}

	SDL_FreeSurface(bmp);
}


Game::~Game(void)
{
	SAFE_DELETE(m_Physics);
	SAFE_DELETE(m_DrawDebug);

	for each (GameObjectRigidBody *obj in GameObjectList)
	{
		SAFE_DELETE(obj);
	}
	GameObjectList.clear();
}

void Game::Update(float _deltaTick, SDL_Event *SDLevent)
{
	//Update physics, all RigidBodies
	if (m_Physics != nullptr)
	{
		m_Physics->stepSimulation(_deltaTick);
	}



	//Pong ball cehck //hack withtout callback
	if (m_PongBall != nullptr)
	{
		m_PongBall->Update(_deltaTick, SDLevent);
		if (m_PongBall->m_RigidBody->m_isColliding)
		{
			m_PongBall->m_RigidBody->m_isColliding = false;

			PlayerPaddle *Player = dynamic_cast<PlayerPaddle*>(m_PongBall->m_RigidBody->m_CurrentCollision.CollidedWith->m_Owner);
			{
				if (Player != nullptr)
				{
					cout << "COLLIDED WITH PLAYER" << endl;
					m_PongBall->m_LastPlayerTouched = Player;
				}
			}

			Wall *wall = dynamic_cast<Wall*>(m_PongBall->m_RigidBody->m_CurrentCollision.CollidedWith->m_Owner);
			//PlayerPaddle *paddle = dynamic_cast<PlayerPaddle*>(m_PongBall->m_RigidBody->m_CurrentCollision.CollidedWith->m_Owner);
			if (wall != nullptr)
			{
				cout << "COLLIDED WITH WALL" << endl;
				if (m_PongBall->m_LastPlayerTouched != nullptr)
				{
					if (wall->GetAssignedPlayer() != nullptr)
					{
						if (m_PongBall->m_LastPlayerTouched != wall->GetAssignedPlayer())
						{
							m_PongBall->m_LastPlayerTouched->SetScore(m_PongBall->m_LastPlayerTouched->GetScore() + 1);
						}
					}
				}
			}

		}
	}

	//update all objects
	for each (GameObjectRigidBody *GameObject in GameObjectList)
	{
		if (GameObject != nullptr)
		{
			GameObject->Update(_deltaTick, SDLevent);
		}
	}

	//check if debug draw is enabled.
	if (DEBUG_DRAW)
	{
		//Draw Stack Added Debug Shapes.
		m_DrawDebug->Update(_deltaTick);
	}
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
		if (GameObject != nullptr)
		{
			GameObject->Render(_ren);
		}
	}

	if (m_PongBall != nullptr)
	{
		m_PongBall->Render(_ren);
	}

	//Render all OnScreenText
	if (m_TextManager != nullptr)
	{
		m_TextManager->Render(_ren);
	}

	//check if debug draw is enabled.
	if (DEBUG_DRAW)
	{
		//Render Debug Shapes
		m_DrawDebug->Render(_ren);
	}

	//Draw This Frame to Screen
	SDL_RenderPresent(_ren);
}

void Game::CreateBorders(spVector2 &_size, SDL_Texture &_texture)
{
	vector<spVector2> Sides;
	Sides.push_back(spVector2((1280 / 2) + (_size.x / 2)* -1, 1024 / 2));
	Sides.push_back(spVector2((1280 / 2) + (_size.x / 2), 1024 / 2));

	bool palyer1 = true;

	for each (spVector2 location in Sides)
	{
		//pShape* shapeBoxTopBot = new pShapeBox(spVector3(_size.x / 2, 10, 0));
		pShape* shapeBoxLeftRight = new pShapeBox(spVector3(10, _size.y / 2, 0));

		GameObjectRigidBody::GORigidBodyConstructor paramaters = GameObjectRigidBody::GORigidBodyConstructor(10000.0f, spVector3(location.x, location.y, 0), shapeBoxLeftRight, &_texture, m_Physics, m_DrawDebug, m_TextManager);
		Wall::WallSetup wallSettings;
		wallSettings.DistanceFromWall = 5;
		wallSettings.OffsetFromWallEdges = 20;
		wallSettings.MaxMoveDistance = 500;
		if (palyer1)
		{
			wallSettings.WallNormalDirection = spVector2(1, 0);
		}
		else
		{
			wallSettings.WallNormalDirection = spVector2(-1, 0);
		}
		Wall * obj = new Wall(wallSettings, paramaters);
		obj->SetTextureSize(spVector2(20, _size.x));
		GameObjectList.push_back(obj);

		if (palyer1)
		{
			obj->AssignPlayerToWall(player1);
			palyer1 = false;
		}
		else
		{
			obj->AssignPlayerToWall(player2);
		}

	}


	vector<spVector2> Sides1;
	Sides1.push_back(spVector2(1280 / 2, (1024 / 2) + (_size.x / 2)* -1));
	Sides1.push_back(spVector2(1280 / 2, (1024 / 2) + (_size.x / 2)));

	for each (spVector2 location in Sides1)
	{
		//pShape* shapeBoxTopBot = new pShapeBox(spVector3(_size.x / 2, 10, 0));
		pShape* shapeBoxTopBottom = new pShapeBox(spVector3(_size.y / 2, 10, 0));

		GameObjectRigidBody::GORigidBodyConstructor paramaters = GameObjectRigidBody::GORigidBodyConstructor(10000.0f, spVector3(location.x, location.y, 0), shapeBoxTopBottom, &_texture, m_Physics, m_DrawDebug, m_TextManager);
		Wall::WallSetup wallSettings;
		wallSettings.DistanceFromWall = 5;
		wallSettings.MaxMoveDistance = 500;
		wallSettings.WallNormalDirection = spVector2(-1, 0);

		Wall * obj = new Wall(wallSettings, paramaters);
		obj->SetTextureSize(spVector2(_size.x, 20));
		GameObjectList.push_back(obj);


	}
}
