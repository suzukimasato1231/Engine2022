#pragma once
#include"Object.h"
#include<vector>
#include <LoadCSV.h>
#include"StegeObject.h"
#include"FishBox.h"
#include"BlockBox.h"
#include"Electricity.h"
#include"DangerFish.h"
#include"MoveFloor.h"
#include"FloorPitfall.h"
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
	void SetFloor(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map, int type);

	void SetBreakBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetJumpBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetWallBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetBreakHard(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetGoal(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetMoveFloor(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetPitfallFloor(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map, int time);

	void SetElectricity(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetFishAttack(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);
private:
	const float mapSize = 25.0f;
	const int drawNumX = 9;
	const int drawNumY = 30;
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
	ObjectData wallOBJ = {};
	int wallGraph = 0;
	const Vec3 wallScale = { 25.0f, 70.0f, 25.0f };
	//ゴール
	ObjectData goalOBJ = {};
	Vec3 goalScale = { 25.0f,25.0f,25.0f };
	bool goalFlag = false;
	//箱
	BlockBox blockBox;
	//電撃の罠
	Electricity elect;
	//危険魚
	DangerFish dangerFish;
private:
	//壊した時に出る魚
	FishBox fishBox;

	int blockMax = 0;//ステージにある最大のブロック数
	int blockNum = 0;	//壊したブロック


	ObjectData blackGround = {};
	int blackGraph = 0;
	PSR blackPsr[3] = {};
};