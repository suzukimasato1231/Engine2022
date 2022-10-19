#include "DangerFish.h"
#include"Shape.h"
DangerFish::DangerFish()
{}

DangerFish::~DangerFish()
{}

void DangerFish::Init()
{
	dangerFishOBJ = Shape::CreateOBJ("cube", true);
}

void DangerFish::Update()
{
	//魚が飛び出すプログラム
	if (dangerFishFlag == true)
	{//飛び出す
		dangerFishTime--;
		if (dangerFishTime <= 0)
		{
			dangerFishFlag = false;
			dangerFishTime = dangerFishTimeMax;
		}
	}
	else
	{//次に飛び出すまでの時間
		dangerFishTime--;
		if (dangerFishTime <= 0)
		{
			dangerFishFlag = true;
			dangerFishTime = dangerFishTimeMax;
		}
	}
}

void DangerFish::Draw(StageOBJ* stageObj, const bool shadowFlag)
{
	if (stageObj == nullptr) { assert(0); }
	Object::Draw(dangerFishOBJ, stageObj->psr, stageObj->position, Vec3(2.0f, 2.0f, 2.0f),
		Vec3(0.0f, 90.0f, 0.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, shadowFlag);
}

StageOBJ DangerFish::SetDangerFish(const Vec3 position, const Vec3 scale, const Vec3 angle, const Vec2 map, const int type)
{
	StageOBJ stageObj = {};
	stageObj.map = { static_cast<float>(map.x),static_cast<float>(map.y) };
	stageObj.position = position;
	stageObj.scale = scale;
	stageObj.angle = angle;
	stageObj.box.maxPosition = XMVectorSet(
		position.x + scale.x / 2,
		position.y + scale.y / 2,
		position.z + scale.z / 2, 1);
	stageObj.box.minPosition = XMVectorSet(
		position.x - scale.x / 2,
		position.y - scale.y / 2,
		position.z - scale.z / 2, 1);
	stageObj.type = type;
	return stageObj;
}
