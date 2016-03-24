#include "Wall.h"



Wall::Wall(const WallSetup &_WallSettings, const GORigidBodyConstructor &_parameters) : GameObjectRigidBody(_parameters)
{
	m_RigidBody = new pRigidBody(_parameters.mass, _parameters.position, _parameters.CollisionShape, this);
	_parameters.physics->AddRigidBody(m_RigidBody);
	m_RigidBody->GetShape()->SetShapeDebugDraw(true);
	pRigidBody::CollisionObjectType type = pRigidBody::COLLISION_OBJECT;
	m_RigidBody->SetObjectType(type);

	m_WallSettings = _WallSettings;

}

Wall::~Wall()
{
}

void Wall::AssignPlayerToWall(PlayerPaddle *_newPlayer)
{
	if (_newPlayer != nullptr)
	{
		m_AssignedPlayer = _newPlayer;
		SetUpPaddle();
	}
}


void Wall::SetUpPaddle()
{
	if (m_AssignedPlayer != nullptr)
	{
		spScalar      m_WallLength = m_TextureSize.y * m_Scale.y;
		spScalar	  m_WallThickness = m_TextureSize.x * m_Scale.x;

		spScalar      m_PaddleLength = m_AssignedPlayer->m_TextureSize.y * m_AssignedPlayer->m_Scale.y;
		spScalar	  m_PaddleThickness = m_AssignedPlayer->m_TextureSize.x * m_AssignedPlayer->m_Scale.x;

		m_AssignedPlayer->m_MaxMoveDistance = (m_WallLength - m_PaddleLength ) / 2 - m_WallSettings.OffsetFromWallEdges;

		//convert to 3d for ease of calc.
		spVector3		WallDirectionIn3D = spVector3(m_WallSettings.WallNormalDirection.x, m_WallSettings.WallNormalDirection.y, 0);

		//Paddle default position is the position of the wall 
		spVector3 PaddleDefaultPosition = m_Position +
			//only need half extents from the wall thickness. // take into accoutn the thickness of the wall/paddle
			WallDirectionIn3D * (m_WallThickness / 2 + m_PaddleThickness /2) +
		//	+the offset in the wall direction +
			WallDirectionIn3D * m_WallSettings.DistanceFromWall;

		//Put Player in Correct Position
		m_AssignedPlayer->m_RigidBody->m_Position = PaddleDefaultPosition;
		//Assign PLayer Default position
		m_AssignedPlayer->m_DefaultPosition = PaddleDefaultPosition;
	}
}

PlayerPaddle *Wall::GetAssignedPlayer()
{
	return m_AssignedPlayer;
}
