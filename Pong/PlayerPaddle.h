#pragma once
#include "GameObjectRigidBody.h"
#include "Text.h"

class PlayerPaddle : public GameObjectRigidBody
{
public:
	PlayerPaddle(const GORigidBodyConstructor &_parameters);
	~PlayerPaddle();

	void SetScore(const int &_newScore);
	int GetScore() const;

	void Update(float _deltaTime, SDL_Event * sdlEvent) override;


	int m_currentScore;

	spVector3 m_PositionOffset;
	spVector3 m_MoveDirection;
	spScalar  m_Speed;
	spScalar  m_MaxMoveDistance;
	spVector3 m_DefaultPosition;

	Text *m_ScoreTextComponent;
	spVector3 m_ScoreTextLocation;
};

