#pragma once
#include"Vec.h"
#include"Enemy.h"
#include "StegeObject.h"
//エネミーマネジャー
class EnemyManager
{
protected:

public:
	EnemyManager();

	~EnemyManager();
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw(bool shadowFlag = false);

	void FloorPush(Floor floor);
private:
	std::vector<Enemy*>enemy;

	ObjectData enemyData;
};

