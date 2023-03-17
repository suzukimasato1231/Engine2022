#include "Electricity.h"
#include<Shape.h>
#include"../player/Player.h"
#include"Collision.h"
#include <LoadCSV.h>
#include<Input.h>
Electricity::Electricity()
{}

Electricity::~Electricity()
{
}

void Electricity::Init()
{
	m_electOBJ = Shape::CreateOBJ("elect", false, "OBJ/");
	m_electShockOBJ = Shape::CreateOBJ("electShock", false, "OBJ/");

	m_electParicle = std::make_unique<ParticleManager>();
	m_electParicle->Initialize();
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
	m_uvScroll += c_uvScrollSpeed;
	if (m_uvScroll.y >= 1.0f)
	{
		m_uvScroll.y = 0.0f;
	}
}

void Electricity::Update(StageData* stageObj)
{
	if (m_electFlag == true)
	{
		if (Collision::CheckBox2Box(stageObj->box, Player::Get()->GetBox()))
		{
			Player::Get()->DieType(ELECTDIE);
		}
	}

	if ((m_electFlag == FALSE && m_electTime < 50) || m_electFlag == true)
	{
		AddElect(stageObj->position, stageObj->scale);
	}
}

void Electricity::Draw(StageData* stageObj, const bool shadowFlag)
{
#ifdef _DEBUG
	if (stageObj == nullptr)
	{
		assert(0);
	}
#endif
	Object::Draw(m_electOBJ, stageObj->psr, stageObj->position, stageObj->scale,
		stageObj->rotation, Vec2(), 0, shadowFlag);

	if (m_electFlag == true)
	{
		Vec3 BasicPos = { -5.5f,0.0f,0.0f };
		BasicPos.x *= stageObj->scale.z;
		Vec3 BasicScale = { 1.0f,1.0f,2.7f };
		Object::DrawUVScroll(m_electShockOBJ, stageObj->psr, stageObj->position + BasicPos * stageObj->scale, stageObj->scale * BasicScale,
			stageObj->rotation, m_uvScroll, 0);
	}
}

void Electricity::DrawParicle()
{
	m_electParicle->Draw(m_electParicleGraph);
}


void Electricity::AddElect(Vec3 pos, Vec3 scale)
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

	Vec3 md_pos = { 20.0f ,5.0f,5.0f };
	md_pos.x *= scale.z;

	for (int i = 0; i < addNum; i++)
	{

		pos.x += (float)rand() / RAND_MAX * md_pos.x - md_pos.x / 2.0f;
		pos.y += (float)rand() / RAND_MAX * md_pos.y - md_pos.y / 2.0f;
		pos.z += (float)rand() / RAND_MAX * md_pos.z - md_pos.z / 2.0f;
		m_electParicle->Add(particleTime, pos, velocity, accel, start_scale, end_scale, start_color, end_color);
	}
}
