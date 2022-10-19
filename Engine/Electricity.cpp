#include "Electricity.h"
#include<Shape.h>
Electricity::Electricity()
{
}

Electricity::~Electricity()
{
}

void Electricity::Init()
{
	electOBJ = Shape::CreateOBJ("elect");

	electShockOBJ = Shape::CreateOBJ("electShock");
}

void Electricity::Update()
{
	//電気ON/OFFプログラム
	if (electFlag == true)
	{
		electTime--;
		if (electTime <= 0)
		{
			electFlag = false;
			electTime = electTimeMax;
		}
	}
	else
	{
		electTime--;
		if (electTime <= 0)
		{
			electFlag = true;
			electTime = electTimeMax;
		}
	}
}

void Electricity::Draw(StageOBJ* stageObj, const bool shadowFlag)
{
	if (stageObj == nullptr) { assert(0); }
	Object::Draw(electOBJ, stageObj->psr, stageObj->position, Vec3(2.0f, 2.0f, 2.0f),
		Vec3(0.0f, 90.0f, 0.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, shadowFlag);

	if (electFlag == true)
	{
		Vec3 pos = { 11.0f,5.0f,0.0f };
		Object::Draw(electShockOBJ, stageObj->psr, stageObj->position + pos, Vec3(1.0f, 2.0f, 5.3f),
			Vec3(0.0f, 90.0f, 0.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, false);
	}

}

StageOBJ Electricity::SetElect(const Vec3 position, const Vec3 scale, const Vec3 angle, const Vec2 map, const int type)
{
	const Vec3 boxScale = {220.0f,40.0f,0.0f};
	StageOBJ stageObj = {};
	stageObj.map = { static_cast<float>(map.x),static_cast<float>(map.y) };
	stageObj.position = position;
	stageObj.scale = scale;
	stageObj.angle = angle;
	stageObj.box.maxPosition = XMVectorSet(
		position.x + boxScale.x / 2,
		position.y + boxScale.y / 2,
		position.z + boxScale.z / 2, 1);
	stageObj.box.minPosition = XMVectorSet(
		position.x - boxScale.x / 2,
		position.y - boxScale.y / 2,
		position.z - boxScale.z / 2, 1);
	stageObj.type = type;
	return stageObj;
}
