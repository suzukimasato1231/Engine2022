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
/// <summary>
/// ステージセレクト
/// </summary>
class StageSelect
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	StageSelect();
	/// <summary>
	/// デスコンストラクタ
	/// </summary>
	~StageSelect();
	//初期化
	void Initialize();
	/// <summary>
	/// 初期化ループ
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
	/// 影の描画
	/// </summary>
	void DrawShadow();

	void StagePlas() { stageNum++; }

	void SetBreakBoxNum(int breakBox_);
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
	const float selectScale = 10.0f;	//セレクトOBJの大きさ
	Vec3 selectPos[stageNumMax];		//セレクトOBJの座標
	Box selectBox[stageNumMax];			//セレクトOBJのBOX
	PSR selectPsr[stageNumMax];			//セレクトOBJのPSR

	//ステージごとの箱の壊した数
	ObjectData boxBreakOBJ = {};		//壊した箱の数を表示する
	ObjectData flameOBJ = {};			//フレーム
	PSR boxBreakPSR[stageNumMax] = {};	//壊した箱のPSR保存
	PSR flamePSR[stageNumMax] = {};		//フレームPSR
	int boxBreakGraph = 0;				//壊した箱の画像
	int boxFramGraph = 0;
	int numberGraph[11] = {};			//数字の画像

	//壊した箱を保存する用
	const int breakBoxMax[3] = { 10,10,10 };
	int breakNumMax[3] = { 0,0,0 };
	int breakNumTenMax[3] = { 0,0,0 };

	int breakBox[3] = { 0,0,0 };
	int breakNum[3] = { 0,0,0 };
	int breakNumTen[3] = { 0,0,0 };


	int stageNum = 0;					//現在のステージ

	//演出
	bool productionFlag[3] = {};
	const int productionTimeMax = 30;
	int productionTime = 0;

	SoundData boxSE = {};
};


