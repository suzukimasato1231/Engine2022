#pragma once
#include "_DirectX.h"
#include "Safe_delete.h"
#include"Collision.h"
#include"Audio.h"
#include"FBXObject3d.h"
#include"Object.h"
extern const int window_width;
extern const int window_height;
class StageSelect 
{

public:
	StageSelect();
	~StageSelect();

	void Initialize();

	void Init();

	void Update();

	void Draw();

	void DrawShadow();
public:
	LightGroup* lightGroup = nullptr;
public:
	int GetStageNum() { return stageNum; }

	bool GetSelectFlag() { return selectFlag; }
private://定義
	static const int stageNumMax = 2;	//最大ステージ数

	bool selectFlag = false;

	ObjectData selectOBJ;
	int selectGraph[stageNumMax];
	float selectScale = 10.0f;
	Vec3 selectPos[stageNumMax];
	Box selectBox[stageNumMax];

	int stageNum = 0;			//現在のステージ
};


