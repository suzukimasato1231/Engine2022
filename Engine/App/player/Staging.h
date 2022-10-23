#pragma once
#include"Vec.h"
#include"ParticleManager.h"
class Staging
{
public://定数
private://メンバ変数
	ParticleManager* particle = nullptr;
	ParticleManager* electDie = nullptr;
	int graph = 0;
public://メンバ関数
	Staging();

	~Staging();
	//初期化処理
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Draw();
	//落下死の生成処理
	void CreateFallDown(Vec3 pPos);
	//感電死の生成処理
	void CreateElect(Vec3 pPos);
};

