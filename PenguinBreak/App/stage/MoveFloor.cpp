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

void MoveFloor::Update(Floor* floorData)
{
	floorData->time++;
	if (floorData->moveFlag == MOVEBACK)
	{
		floorData->position -= c_speed;
		if (floorData->time >= c_timeMax)
		{
			floorData->moveFlag = MOVEFRONT;
			floorData->time = {};
		}
	}
	else
	{
		floorData->position += c_speed;
		if (floorData->time >= c_timeMax)
		{
			floorData->moveFlag = MOVEBACK;
			floorData->time = {};
		}
	}
}

void MoveFloor::Draw(Floor* floorData, const bool shadowFlag)
{
	Object::Draw(m_moveFloorOBJ, floorData->psr, Vec3(floorData->position.x, floorData->position.y - 15.0f, floorData->position.z),
		c_OBJScale, floorData->angle, Vec2(), 0, shadowFlag);
}
