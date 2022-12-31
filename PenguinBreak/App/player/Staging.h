#pragma once
#include"Vec.h"
#include"ParticleManager.h"
#include<vector>
#include"Particle3D.h"
/// <summary>
/// プレイヤー演出クラス
/// </summary>
class Staging
{
private://メンバ変数
	//落下死
	ObjectData fallDown;
	Particle3D* fallParicle;
	//電気死亡
	ParticleManager* electDie = nullptr;
	//歩き
	ParticleManager* walk = nullptr;
	//プレイヤー登場時の演出
	ObjectData startObject;
	Particle3D* startParicle;
	int start_color[3];

	int graph = 0;
public://メンバ関数
	//コンストラクタ
	Staging();
	//デスコンストラクタ
	~Staging();
	//初期化処理
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Draw();
	//3D描画
	void Draw3D();
	//感電死の生成処理
	void CreateElect(Vec3 pPos);
	//歩くの生成処理
	void CreateWalk(Vec3 pPos, Vec3 vec);
	//落下死
	void CreateFallDown(Vec3 pPos);
	//登場時の3Dパーティクル
	void CreateStart(Vec3 pPos);
};

