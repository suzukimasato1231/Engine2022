#include "DangerFish.h"
#include"Shape.h"
#include"Easing.h"
DangerFish::DangerFish()
{}

DangerFish::~DangerFish()
{}

void DangerFish::Init()
{
	m_dangerFishOBJ = Shape::CreateOBJ("dangerFish", true, "OBJ/");
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
	if (m_dangerFishFlag == false) { return; }
	//飛び出す
	if (m_start_endTime < c_start_endTimeMax)
	{
		float t = min(m_start_endTime / c_start_endTimeMax, 1.0f);
		//魚飛び出し
		stageObj->actionPos = Easing::easeOut(stageObj->position, stageObj->position + m_start_end, t);
	}
	else if (m_end_endTime < c_end_endTimeMax)
	{
		float t = min(m_end_endTime / c_end_endTimeMax, 1.0f);
		//魚飛び出し
		stageObj->actionPos = Easing::easeIn(stageObj->position + m_start_end, stageObj->position + m_end_end, t);
	}

	stageObj->box.maxPosition = XMVectorSet(
		stageObj->actionPos.x + c_fishSize.x / 2,
		stageObj->actionPos.y + c_fishSize.y / 2,
		stageObj->actionPos.z + c_fishSize.z / 2, 1);
	stageObj->box.minPosition = XMVectorSet(
		stageObj->actionPos.x - c_fishSize.x / 2,
		stageObj->actionPos.y - c_fishSize.y / 2,
		stageObj->actionPos.z - c_fishSize.z / 2, 1);
}

void DangerFish::AllUpdate()
{
	//魚が飛び出すプログラム
	if (m_dangerFishFlag == true)
	{//飛び出す
		if (m_start_endTime < c_start_endTimeMax)
		{
			//角度が変わるスピード
			const Vec3 angleSpeed = { 0.0f,0.0f,0.5f };
			m_start_endTime++;
			float t = min(m_start_endTime / c_start_endTimeMax, 1.0f);
			m_rotation += angleSpeed;
		}
		else if (m_end_endTime < c_end_endTimeMax)
		{
			//角度が変わるスピード
			const Vec3 angleSpeed = { 0.0f,0.0f,1.0f };
			m_end_endTime++;
			float t = min(m_end_endTime / c_end_endTimeMax, 1.0f);
			m_rotation -= angleSpeed;
		}
		else
		{
			m_dangerFishFlag = false;
			m_dangerFishTime = c_dangerFishTimeMax;
			m_start_endTime = 0;
			m_end_endTime = 0;
		}
	}
	else
	{
		m_dangerFishTime--;
		if (m_dangerFishTime <= 0)
		{
			m_dangerFishFlag = true;
			m_dangerFishTime = c_dangerFishTimeMax;
			m_rotation = c_rotationFirst;
		}
	}
}

void DangerFish::Draw(StageOBJ* stageObj, const bool shadowFlag)
{
#ifdef _DEBUG
	if (stageObj == nullptr)
	{
		assert(0);
	}
#endif
	Object::Draw(m_dangerFishOBJ, stageObj->psr, stageObj->actionPos, Vec3(2.0f, 2.0f, 2.0f),
		m_rotation, Vec2(), 0, shadowFlag);
}

StageOBJ DangerFish::SetDangerFish(const Vec3& position, const Vec3& scale, const Vec3& angle, const int type)
{
	const Vec3 scaleFish = { 25.0f,25.0f,25.0f };
	StageOBJ stageObj = {};
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
