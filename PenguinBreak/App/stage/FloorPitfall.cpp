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
	if (floorData->moveFlag == PITFALLCLOSE)
	{
		if (floorData->time <= 0)
		{
			floorData->time = c_pitfallTime;
			floorData->moveFlag = PITFALLOPEN;
		}
		if (floorData->time <= 5)
		{
			floorData->drawAngle.z += c_pitfallSpeed;
		}
	}//���Ă���
	else if (floorData->moveFlag == PITFALLOPEN)
	{
		if (floorData->time <= 0)
		{
			floorData->time = c_pitfallTime;
			floorData->moveFlag = PITFALLCLOSE;
		}
		if (floorData->time <= 5)
		{
			floorData->drawAngle.z += c_pitfallSpeed;
		}
	}
}

void FloorPitfall::Draw(Floor* floorData, const bool shadowFlag)
{
	if (floorData->moveFlag == PITFALLCLOSE)
	{
		Object::Draw(m_pitfallOBJ, floorData->psr, Vec3(floorData->position.x, floorData->position.y - 2.5f, floorData->position.z), c_pitfallScale,
			floorData->drawAngle, Vec2(), m_pitfallGraph, shadowFlag);
	}//���Ă���
	else if (floorData->moveFlag == PITFALLOPEN)
	{
		Object::Draw(m_pitfallOBJ, floorData->psr, floorData->position, c_pitfallScale,
			floorData->drawAngle, Vec2(), m_pitfallGraph, shadowFlag);
	}
}
