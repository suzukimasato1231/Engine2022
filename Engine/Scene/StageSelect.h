
#pragma once
#include "_DirectX.h"
#include "Safe_delete.h"
#include"DebugText.h"
#include"Collision.h"
#include"Audio.h"
#include"FBXObject3d.h"

extern const int window_width;
extern const int window_height;
class StageSelect :public Singleton<StageSelect>
{
private:
	friend Singleton<StageSelect>;
public:
	StageSelect();
	~StageSelect();

	void Initialize();

	void Init();

	void Update();

	void Draw();
public:
	int GetStageNum() { return stageNumMax; }
	
private://定義
	const int stageNumMax = 1;	//最大ステージ数
	int stageNum = 0;			//現在のステージ
};


