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

	Vec3 GetGoalScale() { return goalScale; }
private:
	//ゴール
	ObjectData goalOBJ = {};
	Vec3 goalScale = { 20.0f,25.0f,20.0f };
	bool goalFlag = false;

	Vec3 angle = { 0.0f,0.0f,0.0f };
};

