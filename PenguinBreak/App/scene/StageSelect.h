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

	void StagePlas() { m_stageNum++; }

	void SetBreakBoxNum(int breakBox_);
public:
	std::unique_ptr<LightGroup>lightGroup;
public:
	int GetStageNum() { return  m_stageNum; }

	bool GetSelectFlag() { return  m_selectFlag; }
private://定義
	static const int c_stageNumMax = 3;	   //最大ステージ数
	int  m_stageNum = 0;				   //現在のステージ
	bool  m_selectFlag = false;			   //次のシーンへ移動

	ObjectData  m_selectOBJ;				//セレクト数字のOBJ
	int  m_selectGraph[c_stageNumMax];		//セレクトOBJの画像
	const float c_selectScale = 10.0f;	    //セレクトOBJの大きさ
	Vec3  m_selectPos[c_stageNumMax];		//セレクトOBJの座標
	Box  m_selectBox[c_stageNumMax];		//セレクトOBJのBOX
	PSR  m_selectPsr[c_stageNumMax];		//セレクトOBJのPSR

	//ステージごとの箱の壊した数
	ObjectData  m_boxBreakOBJ = {};		    //壊した箱の数を表示する
	ObjectData  m_flameOBJ = {};			//フレーム
	PSR  m_boxBreakPSR[c_stageNumMax] = {};	//壊した箱のPSR保存
	PSR  m_flamePSR[c_stageNumMax] = {};	//フレームPSR
	int  m_boxBreakGraph = 0;				//壊した箱の画像
	int  m_boxFramGraph = 0;
	int  m_numberGraph[11] = {};			//数字の画像
	const Vec3 c_numberScale = { 0.3f,0.3f,0.3f };//数字の大きさ
	const Vec3 c_numberAngle = {};                //数字の角度

	//壊した箱を保存する用
	const int c_breakBoxMax[c_stageNumMax] = { 9,11,10 };
	int  m_breakNumMax[c_stageNumMax] = { 0,0,0 };
	int  m_breakNumTenMax[c_stageNumMax] = { 0,0,0 };

	int  m_breakBox[c_stageNumMax] = { 0,0,0 };
	int  m_breakNum[c_stageNumMax] = { 0,0,0 };
	int  m_breakNumTen[c_stageNumMax] = { 0,0,0 };


	//演出
	bool  m_productionFlag[3] = {};
	const int c_productionTimeMax = 30;
	int  m_productionTime = 0;

	SoundData  m_boxSE = {};
};


