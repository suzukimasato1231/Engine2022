#include "FloorPitfall.h"
#include <Shape.h>

FloorPitfall::FloorPitfall()
{}

FloorPitfall::~FloorPitfall()
{}

void FloorPitfall::Init()
{
	pitfallOBJ = Shape::CreateSquare(1.0f, 1.0f, 1.0f);
}

void FloorPitfall::Update(Floor* floorData)
{
	floorData->time--;
	//ŠJ‚¢‚Ä‚¢‚é
	if (floorData->moveFlag == 0)
	{
		if (floorData->time <= 0)
		{
			floorData->time = 50;
			floorData->moveFlag = 1;
		}
		if (floorData->time <= 5)
		{
			floorData->drawAngle.z += 18;
		}
	}//•Â‚¶‚Ä‚¢‚é
	else if (floorData->moveFlag == 1)
	{
		if (floorData->time <= 0)
		{
			floorData->time = 50;
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
		Object::Draw(pitfallOBJ, floorData->psr,Vec3(floorData->position.x, floorData->position.y-2.5f, floorData->position.z) ,Vec3(25.0f,5.0f,25.0f),
			floorData->drawAngle, Vec2(), pitfallGraph, shadowFlag);
	}//•Â‚¶‚Ä‚¢‚é
	else if (floorData->moveFlag == 1)
	{
		Object::Draw(pitfallOBJ, floorData->psr, floorData->position, Vec3(25.0f, 5.0f, 25.0f),
			floorData->drawAngle, Vec2(), pitfallGraph, shadowFlag);
	}
}
