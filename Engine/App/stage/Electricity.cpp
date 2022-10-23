#include "Electricity.h"
#include<Shape.h>
#include"safe_delete.h"
#include"../player/Player.h"
#include"Collision.h"
#include <LoadCSV.h>
Electricity::Electricity()
{}

Electricity::~Electricity()
{
	safe_delete(electParicle);
}

void Electricity::Init()
{
	electOBJ = Shape::CreateOBJ("elect");
	electShockOBJ = Shape::CreateOBJ("electShock");
	electParicle = ParticleManager::Create();
	electParicleGraph = Texture::Get()->LoadTexture(L"Resources/Paricle/elect.png");
}

void Electricity::AllUpdate()
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
	electParicle->Update();
}

void Electricity::Update(StageOBJ* stageObj, const int Z)
{
	if ((MAP_HEIGHT - 1 + Z) - 1 <= stageObj->map.y && stageObj->map.y <= (MAP_HEIGHT - 1 + Z) + 1 && electFlag == true)
	{
		if (Collision::CheckBox2Box(stageObj->box, Player::Get()->GetBox()))
		{
			Player::Get()->DieType(ELECTDIE);
		}
	}

	if (((electFlag == FALSE && electTime < 50) || electFlag == true) &&
		(MAP_HEIGHT - 1 + Z) - 10 <= stageObj->map.y && stageObj->map.y <= (MAP_HEIGHT - 1 + Z) + 10)
	{
		AddElect(stageObj->position);
	}
}

void Electricity::Draw(StageOBJ* stageObj, const bool shadowFlag)
{
#ifdef _DEBUG
	if (stageObj == nullptr)
	{
		assert(0);
	}
#endif
	Object::Draw(electOBJ, stageObj->psr, stageObj->position, Vec3(2.0f, 2.0f, 2.0f),
		Vec3(0.0f, 90.0f, 0.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, shadowFlag);

	if (electFlag == true)
	{
		Vec3 pos = { 11.0f,5.0f,0.0f };
		Object::Draw(electShockOBJ, stageObj->psr, stageObj->position + pos, Vec3(1.0f, 2.0f, 5.3f),
			Vec3(0.0f, 90.0f, 0.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f), 0, false);
	}
}

void Electricity::DrawParicle()
{
	electParicle->Draw(electParicleGraph);
}

StageOBJ Electricity::SetElect(const Vec3 position, const Vec3 scale, const Vec3 angle, const Vec2 map, const int type)
{
	const Vec3 boxScale = { 220.0f,40.0f,0.0f };
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

void Electricity::AddElect(Vec3 pos)
{
	static const int particleTime = 5;
	static const Vec3 velocity = { 0.0f,0.0f,0.0f };
	static const Vec3 accel = { 0.0f,0.0f,0.0f };
	static const float start_scale = 5.0f;
	static const float end_scale = 3.0f;
	static const Vec4 start_color = { 0.5f,0.0f,0.0f,1.0f };
	static const Vec4 end_color = { 0.8f,0.8f,0.0f,1.0f };
	static const int onAddNum = 20;
	static const int offAddNum = 40;
	int addNum = 0;
	if (electFlag == true) { addNum = 30; }
	else { addNum = 10; }

	for (int i = 0; i < addNum; i++)
	{
		//X,Y,Z全て{-5.0f,+5.0f}でランダムに分布
		const Vec3 md_pos = { 100.0f ,5.0f,5.0f };
		pos.x += (float)rand() / RAND_MAX * md_pos.x - md_pos.x / 2.0f;
		pos.y += (float)rand() / RAND_MAX * md_pos.y - md_pos.y / 2.0f;
		pos.z += (float)rand() / RAND_MAX * md_pos.z - md_pos.z / 2.0f;
		electParicle->Add(particleTime, pos, velocity, accel, start_scale, end_scale, start_color, end_color);
	}
}
