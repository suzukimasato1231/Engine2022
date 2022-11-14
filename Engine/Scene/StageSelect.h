#pragma once
#include "_DirectX.h"
#include "Safe_delete.h"
#include"Collision.h"
#include"Audio.h"
#include"FBXObject3d.h"
#include"Object.h"
#include<memory>
extern const int window_width;
extern const int window_height;
class StageSelect 
{

public:
	StageSelect();
	~StageSelect();
	//初期化
	void Initialize();

	void Init();
	//更新
	void Update();
	//描画
	void Draw();
	//影の描画
	void DrawShadow();
public:
	std::unique_ptr<LightGroup>lightGroup;
public:
	int GetStageNum() { return stageNum; }

	bool GetSelectFlag() { return selectFlag; }
private://定義
	static const int stageNumMax = 3;	//最大ステージ数

	bool selectFlag = false;

	ObjectData selectOBJ;
	int selectGraph[stageNumMax];
	float selectScale = 10.0f;
	Vec3 selectPos[stageNumMax];
	Box selectBox[stageNumMax];
	PSR selectPsr[stageNumMax];

	int stageNum = 0;			//現在のステージ
};


