#include "BlockBox.h"
#include"Shape.h"
#include"Texture.h"
#include"../PenguinBreak/App/player/Player.h"
#include"PushCollision.h"
void BlockBox::Init()
{
	m_breakBoxOBJ = Shape::CreateOBJ("cube");
	m_normalBoxGraph = Texture::Get()->LoadTexture(L"Resources/cube/Normal.png");
	m_hardBoxGraph = Texture::Get()->LoadTexture(L"Resources/cube/Hard.png");
	m_jumpBoxgraph = Texture::Get()->LoadTexture(L"Resources/cube/jumpBox.png");
	m_bombBoxGraph = Texture::Get()->LoadTexture(L"Resources/cube/bomb.png");
}

void BlockBox::PlayerHit(StageData* stageObj)
{
	if (Collision::CheckBox2Box(stageObj->box, Player::Get()->GetBox()))
	{
		if (m_box_count >= hitMax) { return; }
		m_obj_data[m_box_count] = *stageObj;
		m_box_count++;
		m_is_hit = true;
	}
}

void BlockBox::PlayerSpinHit(StageData* stageObj)
{
	if (Player::Get()->GetSpinFlag() == false) { return; }

	if (Collision::CheckBox2Box(stageObj->box, Player::Get()->GetSpinBox()))
	{
		if (m_spin_count >= hitMax) { return; }
		m_obj_spin[m_spin_count] = *stageObj;
		m_spin_count++;
		m_is_spin = true;
	}

}

void BlockBox::Draw(StageData* stageObj, const bool shadowFlag)
{
#ifdef _DEBUG
	if (stageObj == nullptr)
	{
		assert(0);
	}
#endif

	if (stageObj->fileName.compare("BOX") == 0)
	{
		Object::Draw(m_breakBoxOBJ, stageObj->psr, stageObj->position, stageObj->scale,
			stageObj->rotation, Vec2(), m_normalBoxGraph, shadowFlag);
	}
	else if (stageObj->fileName.compare("BOXJUMP") == 0)
	{
		Object::Draw(m_breakBoxOBJ, stageObj->psr, stageObj->position, stageObj->scale,
			stageObj->rotation, Vec2(), m_jumpBoxgraph, shadowFlag);
	}
	else if (stageObj->fileName.compare("BOXHARD") == 0)
	{
		Object::Draw(m_breakBoxOBJ, stageObj->psr, stageObj->position, stageObj->scale,
			stageObj->rotation, Vec2(), m_hardBoxGraph, shadowFlag);
	}
	else if (stageObj->fileName.compare("BOXBOMB") == 0)
	{
		Object::Draw(m_breakBoxOBJ, stageObj->psr, stageObj->position + m_bombPlas, stageObj->scale,
			m_bombBoxAngle, Vec2(), m_bombBoxGraph, shadowFlag);
	}
	
}

void BlockBox::BombUpdate()
{
	//”š’e” ‚Ì‰‰o
	m_bombTime++;
	if (m_bombBoxFlag == true)
	{
		m_bombBoxAngle += c_bombSpeedAngle;
		//”š’e‚ª’µ‚Ë‚éˆ—
		if (m_bombTime >= c_bombTimeMax / 2)
		{
			m_bombPlas -= c_bombPlasSpeed;
		}
		else
		{
			m_bombPlas += c_bombPlasSpeed;
		}
		//‰‰oI‚í‚è
		if (m_bombTime >= c_bombTimeMax)
		{
			m_bombBoxFlag = false;
			m_bombTime = {};
		}
	}
	else
	{	//‰‰o‚Í‚¶‚ß
		if (m_bombTime >= c_bombTimeMax)
		{
			m_bombBoxFlag = true;
			m_bombTime = {};
			m_bombPlas = {};
		}
	}
}

void BlockBox::Update()
{
	m_is_hit = false;
	m_box_count = 0;
	m_is_spin = false;
	m_spin_count = 0;
	for (int i = 0; i < hitMax; i++)
	{
		m_obj_data[i] = {};
		m_obj_spin[i] = {};
	}
	//”š’eˆ—‚ÌXV
	BombUpdate();
}

