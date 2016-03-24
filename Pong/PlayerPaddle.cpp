#include "PlayerPaddle.h"
#include <iostream>


PlayerPaddle::PlayerPaddle(const GORigidBodyConstructor &_parameters) : GameObjectRigidBody(_parameters)
{
	m_currentScore = 0;

	m_RigidBody = new pRigidBody(_parameters.mass, _parameters.position, _parameters.CollisionShape ,this);
	_parameters.physics->AddRigidBody(m_RigidBody);
	m_RigidBody->GetShape()->SetShapeDebugDraw(true);
	pRigidBody::CollisionObjectType type = pRigidBody::COLLISION_OBJECT;
	m_RigidBody->SetObjectType(type);

	m_DefaultPosition = spVector3(500,500, 0);
	m_PositionOffset = spVector3(0, 0, 0);
	m_MoveDirection = spVector3(0, 1, 0);
	m_Speed = 1000.0f;
	m_MaxMoveDistance = 505.0f;

	//TEXT
	m_ScoreTextLocation = spVector3(0, 0, 0);
	Text::TextSetup textSetup;
	SDL_Colour newColour;
	newColour.r = 255;
	textSetup._Colour = newColour;
	textSetup._FontName = "lazy.ttf";
	textSetup._FontSize = 200.0f;
	textSetup._Position = m_Position;
	textSetup._Text = "HGELLO GOMASF";

	m_ScoreTextComponent = m_TextManager->CreateNewText(textSetup);
}


PlayerPaddle::~PlayerPaddle()
{

}

void PlayerPaddle::SetScore(const int &_newScore)
{
	m_currentScore = _newScore;
	m_ScoreTextComponent->SetText(std::to_string(_newScore));
}

int PlayerPaddle::GetScore() const
{
	return m_currentScore;
}

void PlayerPaddle::Update(float _deltaTime, SDL_Event * sdlEvent)
{
	GameObjectRigidBody::Update(_deltaTime, sdlEvent);

		//User presses a key
		if (sdlEvent->type == SDL_KEYDOWN)
		{
			//Select surfaces based on key press
			switch (sdlEvent->key.keysym.sym)
			{
			case SDLK_UP:
				std::cout << "up" << std::endl;
				//m_RigidBody->ApplyImpulse(spVector3(1000000, 0, 0));
				//m_RigidBody->m_Position.y += 10 * _deltaTime;

				m_PositionOffset += (m_MoveDirection * -1) * m_Speed * _deltaTime;
				if (m_PositionOffset.Length() > m_MaxMoveDistance)
				{
					m_PositionOffset = (m_MoveDirection * -1 ) * m_MaxMoveDistance;
				}
				m_RigidBody->m_Position = m_DefaultPosition + m_PositionOffset;


				break;

			case SDLK_DOWN:

				std::cout << "down" << std::endl;
				m_PositionOffset += m_MoveDirection * m_Speed * _deltaTime;
				if (m_PositionOffset.Length() > m_MaxMoveDistance)
				{
					m_PositionOffset = m_MoveDirection * m_MaxMoveDistance;
				}
				m_RigidBody->m_Position = m_DefaultPosition + m_PositionOffset;

				//m_RigidBody->ApplyImpulse(spVector3(-100000, 0, 0));
				//m_RigidBody->m_Position.y -= 10 * _deltaTime;
				break;
			}
		}
	
}
