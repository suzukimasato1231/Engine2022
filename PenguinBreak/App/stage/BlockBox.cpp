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
}

void BlockBox::PlayerHit(StageOBJ* stageObj, const int X, const int Z)
{
	if ((X - 1 <= stageObj->map.x && stageObj->map.x <= X + 1)
		&& ((MAP_HEIGHT - 1 + Z) - 1 <= stageObj->map.y && stageObj->map.y <= (MAP_HEIGHT - 1 + Z) + 1))
	{
		if (Collision::CheckBox2Box(stageObj->box, Player::Get()->GetBox()))
		{
			if (box_count >= 4)
			{
				assert(0);
			}
			obj_data[box_count] = *stageObj;
			box_count++;
			is_hit = true;
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
			stageObj->angle, Vec4(1.0f, 1.0f, 1.0f, 1.0f), normalBoxGraph, shadowFlag);
		break;
	case BOXJUMP:
		Object::Draw(breakBoxOBJ, stageObj->psr, stageObj->position, stageObj->scale,
			stageObj->angle, Vec4(1.0f, 1.0f, 1.0f, 1.0f), jumpBoxgraph, shadowFlag);
		break;
	case BOXHARD:
		Object::Draw(breakBoxOBJ, stageObj->psr, stageObj->position, stageObj->scale,
			stageObj->angle, Vec4(1.0f, 1.0f, 1.0f, 1.0f), hardBoxGraph, shadowFlag);
		break;
	}
}

StageOBJ BlockBox::SetBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map,int type)
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


void BlockBox::Update()
{
	is_hit = false;
	box_count = 0;
	for (int i = 0; i < 4; i++)
	{
		obj_data[i] = {};
	}
}
