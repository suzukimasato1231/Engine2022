#pragma once
#include<Object.h>
#include "StegeObject.h"
/// <summary>
/// ゴールクラス
/// </summary>
class GoalFish
{
public:
	//コンストラクタ
	GoalFish();
	//デスコンストラクタ
	~GoalFish();
	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void Draw(StageOBJ* stageObj, const bool shadowFlag);

	Vec3 GetGoalScale() { return m_goalScale; }
private:
	//ゴール
	ObjectData  m_goalOBJ = {};
	Vec3  m_goalScale = { 20.0f,25.0f,20.0f };
	bool  m_goalFlag = false;

	Vec3  m_angle = { 0.0f,0.0f,0.0f };
};

