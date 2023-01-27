#pragma once
#include<vector>
#include <LoadCSV.h>
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
class Player;

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
	void Update(Vec3 pPos);
	//描画
	void Draw(Vec3 pPos, bool shadowFlag = false);

	void DrawParicle();
	//ステージ作成
	void LoadStage(int stageNum);
public://マップ
	bool GetClearFlag() { return goalFlag; }

	int GetBlockNum() { return blockNum; }
	int GetBlockMax() { return blockMax; }
private:
	//川の描画
	void DrawWater();

	void SetFloor(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map, int type, int size = 0);

	void SetBreakBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetJumpBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetWallBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map, int type);

	void SetBreakHard(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetGoal(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetMoveFloor(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetMoveFloor2(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetPitfallFloor(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map, int time);

	void SetElectricity(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetFishAttack(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetFigrineOBJ(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map,int type);
private:
	const float mapSize = 25.0f;
	const int drawNumY = 35;
private://床関連
	//雪の床
	ObjectData floorOBJ;
	std::vector<Floor*>floor;
	int floorGraph = 0;
	//動く床
	MoveFloor moveFloor;

	FloorPitfall floorPitfall;
private://罠ブロック
	std::vector<StageOBJ*>stageObj;
	//壁OBJ
	int wallGraph = 0;
	const Vec3 wallScale = { 25.0f, 70.0f, 25.0f };
	//ゴール
	GoalFish goalFish;
	bool goalFlag = false;
	//箱
	BlockBox blockBox;
	//電撃の罠
	Electricity elect;
	//危険魚
	DangerFish dangerFish;
	//置物
	FigurineOBJ figurineOBJ;
private:
	//壊した時に出る魚
	FishBox fishBox;

	int blockMax = 0;	//ステージにある最大のブロック数
	int blockNum = 0;	//壊したブロック


	ObjectData water = {};
	int waterGraph = 0;
	Vec2 waterUV = {};

	PSR blackPsr[3] = {};
	//落下地点表示クラス
	DropPoint dropPoint;

	BoxStaring boxStaring;

	//サウンド
	SoundData boxSE={};
	SoundData jumpSE = {};
	SoundData goalSE = {};
	bool goalSEFlag = false;
};