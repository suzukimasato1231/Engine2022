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

	bool selectFlag = false;			//次のシーンへ移動
	
	ObjectData selectOBJ;				//セレクト数字のOBJ
	int selectGraph[stageNumMax];		//セレクトOBJの画像
	const float selectScale = 10.0f;			//セレクトOBJの大きさ
	Vec3 selectPos[stageNumMax];		//セレクトOBJの座標
	Box selectBox[stageNumMax];			//セレクトOBJのBOX
	PSR selectPsr[stageNumMax];			//セレクトOBJのPSR

	int stageNum = 0;					//現在のステージ

	//演出
	bool productionFlag[3] = {};
	const int productionTimeMax = 30;
	int productionTime = 0;


};


