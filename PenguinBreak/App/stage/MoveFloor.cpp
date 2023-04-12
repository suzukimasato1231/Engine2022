#include "MoveFloor.h"
#include"Shape.h"
MoveFloor::MoveFloor()
{}

MoveFloor::~MoveFloor()
{}

void MoveFloor::Init()
{
	m_moveFloorOBJ = Shape::CreateOBJ("ice", false, "OBJ/");
}

void MoveFloor::Update(StageData* floorData)
{
	floorData->actionTime++;
	if (floorData->actionType == static_cast<int>(MoveType::MOVEBACK))
	{
		floorData->position -= c_speed;
		if (floorData->actionTime >= c_timeMax)
		{
			floorData->actionType = static_cast<int>(MoveType::MOVEFRONT);
			floorData->actionTime = {};
		}
	}
	else
	{
		floorData->position += c_speed;
		if (floorData->actionTime >= c_timeMax)
		{
			floorData->actionType = static_cast<int>(MoveType::MOVEBACK);
			floorData->actionTime = {};
		}
	}
}

void MoveFloor::Draw(StageData* floorData, const bool shadowFlag)
{
	Object::Draw(m_moveFloorOBJ, floorData->psr, Vec3(floorData->position.x, floorData->position.y, floorData->position.z),
		floorData->scale, Vec3(floorData->rotation.x, floorData->rotation.y, floorData->rotation.z), Vec2(), {}, shadowFlag);
}
