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
	void Update(StageOBJ* stageObj, const int Z);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="stageObj">ステージデータ</param>
	/// <param name="shadowFlag">影フラグ</param>
	void Draw(StageOBJ* stageObj, const bool shadowFlag);
	/// <summary>
	/// パーティクル描画
	/// </summary>
	void DrawParicle();

	static StageOBJ SetElect(const Vec3& position, const Vec3& scale, const Vec3& angle, const Vec2& map, const int type);
private:
	//電気パーティクル
	void AddElect(Vec3 pos);
private:
	//電気柱オブジェクト
	ObjectData m_electOBJ;
	//電気オブジェクト
	ObjectData m_electShockOBJ;

	//電気ON/OFF
	bool m_electFlag = false;
	//電気切り替え最大時間時間
	const int c_electTimeMax = 150;
	//切り替えまでの時間
	int m_electTime = 0;
	//電気びりびり
	std::unique_ptr<ParticleManager>m_electParicle = nullptr;
	int m_electParicleGraph = 0;

	Vec2 m_uvScroll = { 0.0f ,0.0f };
};

