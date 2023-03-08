#include "FloorPitfall.h"
#include <Shape.h>

FloorPitfall::FloorPitfall()
{}

FloorPitfall::~FloorPitfall()
{}

void FloorPitfall::Init()
{
	m_pitfallOBJ = Shape::CreateSquare(1.0f, 1.0f, 1.0f);
}

void FloorPitfall::Update(Floor* floorData)
{
	floorData->time--;
	//�J���Ă���
	if (floorData->moveFlag == 0)
	{
		if (floorData->time <= 0)
		{
			floorData->time = c_pitfallTime;
			floorData->moveFlag = 1;
		}
		if (floorData->time <= 5)
		{
			floorData->drawAngle.z += 18;
		}
	}//���Ă���
	else if (floorData->moveFlag == 1)
	{
		if (floorData->time <= 0)
		{
			floorData->time = c_pitfallTime;
			floorData->moveFlag = 0;
		}
		if (floorData->time <= 5)
		{
			floorData->drawAngle.z += 18;
		}
	}
}

void FloorPitfall::Draw(Floor* floorData, const bool shadowFlag)
{
	if (floorData->moveFlag == 0)
	{
		Object::Draw(m_pitfallOBJ, floorData->psr,Vec3(floorData->position.x, floorData->position.y-2.5f, floorData->position.z) ,Vec3(25.0f,5.0f,25.0f),
			floorData->drawAngle, Vec2(), m_pitfallGraph, shadowFlag);
	}//���Ă���
	else if (floorData->moveFlag == 1)
	{
		Object::Draw(m_pitfallOBJ, floorData->psr, floorData->position, Vec3(25.0f, 5.0f, 25.0f),
			floorData->drawAngle, Vec2(), m_pitfallGraph, shadowFlag);
	}
}
