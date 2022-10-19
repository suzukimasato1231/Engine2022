#include "DangerFish.h"
#include"Shape.h"
#include"Easing.h"
DangerFish::DangerFish()
{}

DangerFish::~DangerFish()
{}

void DangerFish::Init()
{
	dangerFishOBJ = Shape::CreateOBJ("dangerFish", true);
}

void DangerFish::Update(StageOBJ* stageObj)
{
#ifdef _DEBUG
	if (stageObj == nullptr)
	{
		assert(0);
	}
#endif
	//魚が飛び出すプログラム
	if (dangerFishFlag == true)
	{//飛び出す
		if (start_endTime < start_endTimeMax)
		{
			start_endTime++;
			float t = min(start_endTime / start_endTimeMax, 1.0f);
			//魚飛び出し
			stageObj->actionPos = Easing::easeOut(stageObj->position, stageObj->position + start_end, t);
			rotation += Vec3(0.0f, 0.0f, 0.5f);
		}
		else if (end_endTime < end_endTimeMax)
		{
			end_endTime++;
			float t = min(end_endTime / end_endTimeMax, 1.0f);
			//魚飛び出し
			stageObj->actionPos = Easing::easeIn(stageObj->position + start_end, stageObj->position + end_end, t);
			rotation -= Vec3(0.0f, 0.0f, 1.0f);
		}
		else
		{
			dangerFishFlag = false;
			dangerFishTime = dangerFishTimeMax;
			start_endTime = 0;
			end_endTime = 0;
		}
	}
	else
	{
		dangerFishTime--;
		if (dangerFishTime <= 0)
		{
			dangerFishFlag = true;
			dangerFishTime = dangerFishTimeMax;
			rotation = { 0.0f,180.0f,0.0f };
		}
	}

	stageObj->box.maxPosition = XMVectorSet(
		stageObj->actionPos.x + fishSize.x / 2,
		stageObj->actionPos.y + fishSize.y / 2,
		stageObj->actionPos.z + fishSize.z / 2, 1);
	stageObj->box.minPosition = XMVectorSet(
		stageObj->actionPos.x - fishSize.x / 2,
		stageObj->actionPos.y - fishSize.y / 2,
		stageObj->actionPos.z - fishSize.z / 2, 1);
}

void DangerFish::Draw(StageOBJ* stageObj, const bool shadowFlag)
{
#ifdef _DEBUG
	if (stageObj == nullptr)
	{
		assert(0);
	}
#endif
	Object::Draw(dangerFishOBJ, stageObj->psr, stageObj->actionPos, Vec3(2.0f, 2.0f, 2.0f),
		rotation, Vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, shadowFlag);
}

StageOBJ DangerFish::SetDangerFish(const Vec3 position, const Vec3 scale, const Vec3 angle, const Vec2 map, const int type)
{
	Vec3 scaleFish = { 25.0f,25.0f,25.0f };
	StageOBJ stageObj = {};
	stageObj.map = { static_cast<float>(map.x),static_cast<float>(map.y) };
	stageObj.position = position + Vec3(0.0f, -40.0f, 0.0f);
	stageObj.scale = scale;
	stageObj.angle = angle;
	stageObj.box.maxPosition = XMVectorSet(
		position.x + scaleFish.x / 2,
		position.y + scaleFish.y / 2,
		position.z + scaleFish.z / 2, 1);
	stageObj.box.minPosition = XMVectorSet(
		position.x - scaleFish.x / 2,
		position.y - scaleFish.y / 2,
		position.z - scaleFish.z / 2, 1);
	stageObj.type = type;
	stageObj.actionPos = stageObj.position;
	return stageObj;
}
