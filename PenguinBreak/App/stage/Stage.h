#pragma once
#include<vector>
#include"FishBox.h"
#include"BlockBox.h"
#include"Electricity.h"
#include"DangerFish.h"
#include"MoveFloor.h"
#include"FloorPitfall.h"
#include"DropPoint.h"
#include"GoalFish.h"
#include"BoxStaring.h"
#include"FigurineOBJ.h"
#include<Audio.h>
#include<LoadJson.h>
class Player;
/// <summary>
/// ステージクラス
/// </summary>
class Stage :public Singleton<Stage>
{
private:
	friend Singleton<Stage>;
public:
	//コンストラクタ
	Stage();
	//デスコンストラクタ
	~Stage();
	//初期化
	void Init();
	//ステージ選択
	void MainInit(int stageNum);
	//更新
	void Update(const Vec3& pPos);
	//描画
	void Draw(const Vec3& pPos, bool shadowFlag = false);
	//パーティクル描画
	void DrawParicle();
	//ステージ作成
	void LoadStage(int stageNum);
public://マップ
	inline bool GetClearFlag() { return m_goalFlag; }
	inline int GetBlockNum() { return m_blockNum; }
	inline int GetBlockMax() { return m_blockMax; }
private:
	//川の描画
	void DrawWater();
	//壊れる箱の処理
	void BreakBoxs();
	//箱関連か
	bool CheckBoxJudge(StageData* stageData);
	//置物関連か
	bool CheckFigurineJudge(StageData* stageData);
	//ステージ上の調整
	void SetStageBox(StageData* stageData, const Vec3& scale);
	//床の当たり判定と足元表示
	void FloorHitDropPoint(StageData* s, const Vec3& PPos);
private:
	const float c_mapSize = 25.0f;
	const int c_drawNumY = 35;
private://床関連
	//雪の床
	ObjectData m_floorOBJ;
	int m_floorGraph = 0;
	//動く床
	MoveFloor m_moveFloor;

	FloorPitfall m_floorPitfall;
private://罠ブロック
	//壁OBJ
	int m_wallGraph = 0;
	const Vec3 m_wallScale = { 25.0f, 70.0f, 25.0f };
	//ゴール
	GoalFish m_goalFish;
	bool m_goalFlag = false;
	//箱
	BlockBox m_blockBox;
	const Vec3 boxScale = { 20.0f ,20.0f,20.0f };
	//電撃の罠
	Electricity m_elect;
	//危険魚
	DangerFish m_dangerFish;
	//置物
	FigurineOBJ m_figurineOBJ;
private:
	//壊した時に出る魚
	FishBox m_fishBox;

	int m_blockMax = 0;	//ステージにある最大のブロック数
	int m_blockNum = 0;	//壊したブロック


	ObjectData m_water = {};
	int m_waterGraph = 0;
	Vec2 m_waterUV = {};

	PSR m_blackPsr[6][4] = {};
	//落下地点表示クラス
	DropPoint m_dropPoint;

	BoxStaring m_boxStaring;

	//サウンド
	SoundData m_boxSE = {};
	SoundData m_jumpSE = {};
	SoundData m_goalSE = {};
	SoundData m_bombSE = {};
	bool m_goalSEFlag = false;

	std::vector<StageData*>stageData;
	LevelData* levelData = nullptr;
};