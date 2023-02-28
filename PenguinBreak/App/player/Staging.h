#pragma once
#include"Vec.h"
#include"ParticleManager.h"
#include<vector>
#include"Particle3D.h"
#include<memory>
/// <summary>
/// プレイヤー演出クラス
/// </summary>
class Staging
{
private://メンバ変数
	//落下死
	ObjectData fallDown;
	std::unique_ptr<Particle3D> fallParicle = nullptr;
	//電気死亡
	std::unique_ptr<ParticleManager>electDie = nullptr;
	//歩き
	std::unique_ptr<ParticleManager> walk = nullptr;
	//プレイヤー登場時の演出
	ObjectData startObject;
	std::unique_ptr<Particle3D> startParicle;
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
	void CreateElect(const Vec3 pPos);
	//歩くの生成処理
	void CreateWalk(const Vec3& pPos, const Vec3& vec);
	//落下死
	void CreateFallDown(const Vec3& pPos);
	//登場時の3Dパーティクル
	void CreateStart(const Vec3& pPos);
};

