#include "Electricity.h"
#include<Shape.h>
#include"safe_delete.h"
#include"../player/Player.h"
#include"Collision.h"
#include <LoadCSV.h>
#include<Input.h>
Electricity::Electricity()
{}

Electricity::~Electricity()
{
	safe_delete(m_electParicle);
}

void Electricity::Init()
{
	m_electOBJ = Shape::CreateOBJ("elect", false, "OBJ/");
	m_electShockOBJ = Shape::CreateOBJ("electShock", false, "OBJ/");
	m_electParicle = ParticleManager::Create();
	m_electParicleGraph = Texture::Get()->LoadTexture(L"Resources/Paricle/elect.png");
}

void Electricity::AllUpdate()
{
	//電気ON/OFFプログラム
	if (m_electFlag == true)
	{
		m_electTime--;
		if (m_electTime <= 0)
		{
			m_electFlag = false;
			m_electTime = c_electTimeMax;
		}
	}
	else
	{
		m_electTime--;
		if (m_electTime <= 0)
		{
			m_electFlag = true;
			m_electTime = c_electTimeMax;
		}
	}
	m_electParicle->Update();
	//UVスクロール
	uvScroll += {0.0f, 0.002f};
	if (uvScroll.y >= 1.0f)
	{
		uvScroll.y = 0.0f;
	}

}

void Electricity::Update(StageOBJ* stageObj, const int Z)
{
	if ((MAP_HEIGHT - 1 + Z) - 1 <= stageObj->map.y && stageObj->map.y <= (MAP_HEIGHT - 1 + Z) + 1 && m_electFlag == true)
	{
		if (Collision::CheckBox2Box(stageObj->box, Player::Get()->GetBox()))
		{
			Player::Get()->DieType(ELECTDIE);
		}
	}

	if (((m_electFlag == FALSE && m_electTime < 50) || m_electFlag == true) &&
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
	Object::Draw(m_electOBJ, stageObj->psr, stageObj->position, Vec3(2.0f, 2.0f, 2.0f),
		Vec3(0.0f, 90.0f, 0.0f), Vec2(), 0, shadowFlag);

	if (m_electFlag == true)
	{
		Vec3 pos = { 11.0f,5.0f,0.0f };
		Object::DrawUVScroll(m_electShockOBJ, stageObj->psr, stageObj->position + pos, Vec3(1.0f, 2.0f, 5.3f),
			Vec3(0.0f, 90.0f, 0.0f), uvScroll, 0);
	}
}

void Electricity::DrawParicle()
{
	m_electParicle->Draw(m_electParicleGraph);
}

StageOBJ Electricity::SetElect(const Vec3 &position, const Vec3 &scale, const Vec3 &angle, const Vec2 &map, const int type)
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
	if (m_electFlag == true) { addNum = 20; }
	else { addNum = 5; }

	for (int i = 0; i < addNum; i++)
	{
		//X,Y,Z全て{-5.0f,+5.0f}でランダムに分布
		const Vec3 md_pos = { 100.0f ,5.0f,5.0f };
		pos.x += (float)rand() / RAND_MAX * md_pos.x - md_pos.x / 2.0f;
		pos.y += (float)rand() / RAND_MAX * md_pos.y - md_pos.y / 2.0f;
		pos.z += (float)rand() / RAND_MAX * md_pos.z - md_pos.z / 2.0f;
		m_electParicle->Add(particleTime, pos, velocity, accel, start_scale, end_scale, start_color, end_color);
	}
}
