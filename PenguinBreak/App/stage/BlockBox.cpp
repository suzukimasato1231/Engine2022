#include "BlockBox.h"
#include"Shape.h"
#include"Texture.h"
#include"../PenguinBreak/App/player/Player.h"
#include"PushCollision.h"
void BlockBox::Init()
{
	breakBoxOBJ = Shape::CreateOBJ("cube");
	normalBoxGraph = Texture::Get()->LoadTexture(L"Resources/cube/Normal.png");
	hardBoxGraph = Texture::Get()->LoadTexture(L"Resources/cube/Hard.png");
	jumpBoxgraph = Texture::Get()->LoadTexture(L"Resources/cube/jumpBox.png");
	bombBoxGraph = Texture::Get()->LoadTexture(L"Resources/cube/bomb.png");
}

void BlockBox::PlayerHit(StageOBJ* stageObj, const int X, const int Z)
{
	if ((X - 1 <= stageObj->map.x && stageObj->map.x <= X + 1)
		&& ((MAP_HEIGHT - 1 + Z) - 1 <= stageObj->map.y && stageObj->map.y <= (MAP_HEIGHT - 1 + Z) + 1))
	{
		if (Collision::CheckBox2Box(stageObj->box, Player::Get()->GetBox()))
		{
			if (box_count >= 4) { return; }
			obj_data[box_count] = *stageObj;
			box_count++;
			is_hit = true;
		}
	}
}

void BlockBox::PlayerSpinHit(StageOBJ* stageObj, const int X, const int Z)
{
	if (Player::Get()->GetSpinFlag() == false) { return; }
	if ((X - 3 <= stageObj->map.x && stageObj->map.x <= X + 3)
		&& ((MAP_HEIGHT - 1 + Z) - 3 <= stageObj->map.y && stageObj->map.y <= (MAP_HEIGHT - 1 + Z) + 3))
	{
		if (Collision::CheckBox2Box(stageObj->box, Player::Get()->GetSpinBox()))
		{
			if (spin_count >= 4) { return; }
			obj_spin[spin_count] = *stageObj;
			spin_count++;
			is_spin = true;
		}
	}
}

void BlockBox::Draw(StageOBJ* stageObj, const bool shadowFlag)
{
#ifdef _DEBUG
	if (stageObj == nullptr)
	{
		assert(0);
	}
#endif
	switch (stageObj->type)
	{
	case BOX:
		Object::Draw(breakBoxOBJ, stageObj->psr, stageObj->position, stageObj->scale,
			stageObj->angle, Vec2(), normalBoxGraph, shadowFlag);
		break;
	case BOXJUMP:
		Object::Draw(breakBoxOBJ, stageObj->psr, stageObj->position, stageObj->scale,
			stageObj->angle, Vec2(), jumpBoxgraph, shadowFlag);
		break;
	case BOXHARD:
		Object::Draw(breakBoxOBJ, stageObj->psr, stageObj->position, stageObj->scale,
			stageObj->angle, Vec2(), hardBoxGraph, shadowFlag);
		break;
	case BOXBOMB:
		Object::Draw(breakBoxOBJ, stageObj->psr, stageObj->position + bombPlas, stageObj->scale,
			bombBoxAngle, Vec2(), bombBoxGraph, shadowFlag);
		break;
	}
}

void BlockBox::BombUpdate()
{
	//���e���̉��o
	bombTime++;
	if (bombBoxFlag == true)
	{
		bombBoxAngle += bombSpeedAngle;
		//���e�����˂鏈��
		if (bombTime >= bombTimeMax / 2)
		{
			bombPlas -= bombPlasSpeed;
		}
		else
		{
			bombPlas += bombPlasSpeed;
		}
		//���o�I���
		if (bombTime >= bombTimeMax)
		{
			bombBoxFlag = false;
			bombTime = {};
		}
	}
	else
	{	//���o�͂���
		if (bombTime >= bombTimeMax)
		{
			bombBoxFlag = true;
			bombTime = {};
			bombPlas = {};
		}
	}
}

void BlockBox::Update()
{
	is_hit = false;
	box_count = 0;
	is_spin = false;
	spin_count = 0;
	for (int i = 0; i < 4; i++)
	{
		obj_data[i] = {};
		obj_spin[i] = {};
	}
	//���e�����̍X�V
	BombUpdate();
}

