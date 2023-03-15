#pragma once
#include<Object.h>
#include "StegeObject.h"
/// <summary>
/// ゴールクラス
/// </summary>
class GoalFish
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GoalFish();
	/// <summary>
	/// デスコンストラクタ
	/// </summary>
	~GoalFish();
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
	/// <param name="stageObj">ステージデータ</param>
	/// <param name="shadowFlag">影フラグ</param>
	void Draw(StageData* stageObj, const bool shadowFlag);

	Vec3 GetGoalScale() { return m_goalScale; }
private:
	//ゴール
	ObjectData  m_goalOBJ = {};					//金色魚OBJ
	Vec3  m_goalScale = { 20.0f,25.0f,20.0f };	//魚のサイズ
	const Vec3 c_OBJScale = { 3.0f,3.0f,3.0f };	//OBJの拡大数
	bool  m_goalFlag = false;					//ゴールしたかのフラグ
	Vec3 m_goalAngle = { 0.0f,0.0f,180.0f };	//魚の角度
	const float c_angleSpeed = 1.0f;			//角度が変わるスピード
	const float c_angleMax = 360.0f;			//角度の最大
};

