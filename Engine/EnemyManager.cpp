#include "EnemyManager.h"
#include"PushCollision.h"
#include"Shape.h"
EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
	for (int i = (int)enemy.size() - 1; i >= 0; i--)
	{
		delete enemy[i];
		enemy.erase(enemy.begin() + i);
	}
}

void EnemyManager::Init()
{
	//1éÌóﬁñ⁄ÇÃìGÇÃèâä˙âª
	enemyData = Shape::CreateSquare(10.0f, 10.0f, 10.0f);

	enemy.push_back(new Enemy);
	enemy[enemy.size() - 1]->SetPos(Vec3(100.0f, 0.0f, 400.0f));


}

void EnemyManager::Update()
{
	
}

void EnemyManager::Draw(bool shadowFlag)
{
	for (int num = 0; num < enemy.size(); num++)
	{//ï`âÊ
		Object::Draw(enemyData, enemy[num]->GetPos(), enemy[num]->GetSize(),
			Vec3(), Vec4(), 0, shadowFlag);
	}
}

void EnemyManager::FloorPush(Floor floor)
{
	//è∞Ç∆ÇÃâüÇµñﬂÇµ
	for (int num = 0; num < enemy.size(); num++)
	{
		enemy[num]->SetPos(PushCollision::Enemy2Floor(
			floor.position, floor.angle, floor.scale,
			enemy[num]->GetPos(), enemy[num]->GetSize()
		));
	}
}
