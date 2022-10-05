#pragma once
#include"Object.h"
#include<vector>
#include <LoadCSV.h>
#include"./StegeObject.h"
#include"../Engine/EnemyManager.h"
#include"FishBox.h"
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

	void LoadStage(int stageNum);
public://マップ
	bool GetClearFlag() { return goalFlag; }

	int GetBlockNum() { return blockNum; }
	int GetStageBlock() { return stageBlockNum; }
private:
	void SetFloor(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map, int type);

	void SetBreakBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetJumpBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetWallBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetBreakHard(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetGoal(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetMoveFloor(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetPitfallFloor(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map, int time);

	void MoveFloorUpdate(int i);

	void PitfallUpdate(int i);
private:
	const float mapSize = 25.0f;
	const int drawNumX = 10;
	const int drawNumY = 30;
	////ブロック
	int	map[MAP_HEIGHT][MAP_WIDTH] = {};		//マップチップ
	int mapPos[MAP_HEIGHT][MAP_WIDTH] = {};

	int mapOBJ[MAP_HEIGHT][MAP_WIDTH] = {};		//壁などのOBJ
	int mapOBJPos[MAP_HEIGHT][MAP_WIDTH] = {};	//壁などのOBJの座標

	//雪の床
	ObjectData floorOBJ;
	std::vector<Floor*>floor;


	std::vector<StageOBJ*>stageObj;
	//壁OBJ
	ObjectData wallOBJ = {};
	int wallGraph = 0;
	const Vec3 wallScale = { 25.0f, 70.0f, 25.0f };
	//ゴール
	ObjectData goalOBJ = {};
	Vec3 goalScale = { 25.0f,25.0f,25.0f };
	bool goalFlag = false;
	//壊れる箱
	ObjectData breakBoxOBJ = {};
	Vec3 breakBoxScale = { 20.0f,20.0f,20.0f };
	int normalBoxGraph = 0;
	int breakBoxGraph = 0;
	int jumpBoxgraph = 0;

	FishBox fishBox;

	int stageBlockNum = 0;//ステージにある最大のブロック数
	int blockNum = 0;	//壊したブロック

	//動く床
	ObjectData moveFloorOBJ = {};
	std::vector<MoveFloorData*>moveFloorData;
	int moveGraph = 0;

	//落とし床
	ObjectData floorPitfallOBJ = {};
	std::vector<FloorPitfallData*>floorPitfallData;
	int pitfallGraph = 0;


	ObjectData blackGround = {};
	int blackGraph = 0;
};