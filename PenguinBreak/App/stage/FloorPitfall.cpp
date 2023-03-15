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

void FloorPitfall::Update(StageData* floorData)
{
	floorData->actionTime--;
	//ŠJ‚¢‚Ä‚¢‚é
	if (floorData->actionType == PITFALLCLOSE)
	{
		if (floorData->actionTime <= 0)
		{
			floorData->actionTime = c_pitfallTime;
			floorData->actionType = PITFALLOPEN;
		}
		if (floorData->actionTime <= 5)
		{
			floorData->rotation.z += c_pitfallSpeed;
		}
	}//•Â‚¶‚Ä‚¢‚é
	else if (floorData->actionType == PITFALLOPEN)
	{
		if (floorData->actionTime <= 0)
		{
			floorData->actionTime = c_pitfallTime;
			floorData->actionType = PITFALLCLOSE;
		}
		if (floorData->actionTime <= 5)
		{
			floorData->rotation.z += c_pitfallSpeed;
		}
	}
}

void FloorPitfall::Draw(StageData* floorData, const bool shadowFlag)
{
	if (floorData->actionType == PITFALLCLOSE)
	{
		Object::Draw(m_pitfallOBJ, floorData->psr, Vec3(floorData->position.x, floorData->position.y - 2.5f, floorData->position.z), c_pitfallScale,
			floorData->rotation, Vec2(), m_pitfallGraph, shadowFlag);
	}//•Â‚¶‚Ä‚¢‚é
	else if (floorData->actionType == PITFALLOPEN)
	{
		Object::Draw(m_pitfallOBJ, floorData->psr, floorData->position, c_pitfallScale,
			floorData->rotation, Vec2(), m_pitfallGraph, shadowFlag);
	}
}
