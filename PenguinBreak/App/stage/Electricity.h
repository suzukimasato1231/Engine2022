#pragma once
#include"StegeObject.h"
#include"ParticleManager.h"
#include<memory>
/// <summary>
/// 電気の罠
/// </summary>
class Electricity
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Electricity();
	/// <summary>
	/// デスコンストラクタ
	/// </summary>
	~Electricity();
	/// <summary>
	/// 初期化
	/// </summary>
	void Init();
	/// <summary>
	/// 全体の更新
	/// </summary>
	void AllUpdate();
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="stageObj">ステージデータ</param>
	/// <param name="Z">Z軸位置</param>
	void Update(StageData* stageObj);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="stageObj">ステージデータ</param>
	/// <param name="shadowFlag">影フラグ</param>
	void Draw(StageData* stageObj, const bool shadowFlag);
	/// <summary>
	/// パーティクル描画
	/// </summary>
	void DrawParicle();
private:
	//電気パーティクル
	void AddElect(Vec3 pos, Vec3 scale);
private:
	ObjectData m_electOBJ;			//電気柱オブジェクト
	ObjectData m_electShockOBJ;		//電気オブジェクト
	bool m_electFlag = false;		//電気ON/OFF
	const int c_electTimeMax = 150;	//電気切り替え最大時間時間
	int m_electTime = 0;			//切り替えまでの時間
	//電気びりびり
	std::unique_ptr<ParticleManager>m_electParicle = nullptr;
	TextureData m_electParicleGraph = {};

	const Vec2 c_uvScrollSpeed = { 0.0f, 0.002f };	//uvスクロール速度
	Vec2 m_uvScroll = { 0.0f ,0.0f };				//uv位置
};

