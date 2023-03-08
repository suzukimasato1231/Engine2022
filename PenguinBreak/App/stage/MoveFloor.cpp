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
	if (floorData->moveFlag == 1)
	{
		floorData->position -= m_speed;
		if (floorData->time >= 150)
		{
			floorData->moveFlag = 0;
			floorData->time = 0;
		}
	}
	else
	{
		floorData->position += m_speed;
		if (floorData->time >= 150)
		{
			floorData->moveFlag = 1;
			floorData->time = 0;
		}
	}
}

void MoveFloor::Draw(Floor* floorData, const bool shadowFlag)
{
	Object::Draw(m_moveFloorOBJ, floorData->psr, Vec3(floorData->position.x, floorData->position.y - 15.0f, floorData->position.z),
		Vec3(12.5f, 12.5f, 12.5f) * 2, floorData->angle, Vec2(), 0, shadowFlag);
}
