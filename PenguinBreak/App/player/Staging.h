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
	ObjectData  m_fallDown;
	std::unique_ptr<Particle3D>  paricle3D = nullptr;
	//電気死亡
	std::unique_ptr<ParticleManager> particle = nullptr;
	//プレイヤー登場時の演出
	ObjectData  m_startObject;
	TextureData  m_start_color[3]={};

	TextureData  m_graph = {};
public://メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Staging();
	/// <summary>
	/// デスコンストラクタ
	/// </summary>
	~Staging();
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
	void Draw();
	/// <summary>
	/// 3D描画
	/// </summary>
	void Draw3D();
	/// <summary>
	/// 感電死の生成処理
	/// </summary>
	void CreateElect(const Vec3 pPos);
	/// <summary>
	/// 歩くパーティクルの生成処理
	/// </summary>
	void CreateWalk(const Vec3& pPos, const Vec3& vec);
	/// <summary>
	/// 落下死のパーティクル生成処理
	/// </summary>
	void CreateFallDown(const Vec3& pPos);
	/// <summary>
	/// 登場時のパーティクル生成処理
	/// </summary>
	void CreateStart(const Vec3& pPos);
};

