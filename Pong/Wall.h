#pragma once
#include "GameObjectRigidBody.h"
#include "PlayerPaddle.h"
#include "spVector2.h"


class Wall : public GameObjectRigidBody
{
public:

	struct WallSetup
	{
		float DistanceFromWall;
		float MaxMoveDistance;
		spVector2 WallNormalDirection;
		float OffsetFromWallEdges;
	};

	Wall(const WallSetup &_WallSettings, const GORigidBodyConstructor &_parameters);;
	~Wall();

	void AssignPlayerToWall(PlayerPaddle *_newPlayer);
	void SetUpPaddle();
	PlayerPaddle * GetAssignedPlayer();

private:
	//Reference to a player who is assigned to this wall
	PlayerPaddle *m_AssignedPlayer;
	//Settings that help setup the position and moving direction of the palyer paddle based on this wall.
	WallSetup	  m_WallSettings;



};

