#pragma once
#include"Vec.h"
#include"ParticleManager.h"
class PlayerFallDie
{
public://定数
private://メンバ変数
	ParticleManager* particle = nullptr;

	int graph = 0;
public://メンバ関数
	PlayerFallDie();

	~PlayerFallDie();
	//初期化処理
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Draw();
	//生成処理
	void Create(Vec3 pPos);
};

