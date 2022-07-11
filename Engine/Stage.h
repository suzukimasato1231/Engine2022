#pragma once
#include"Object.h"
#include<vector>
#include <LoadCSV.h>
#include"./StegeObject.h"
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
	void Update();
	//描画
	void Draw();
public://マップ
	int GetMap(int i, int j) { return map[j][i]; }

	bool GetClearFlag() { return goalFlag; }

	int GetBlockNum() { return blockNum; }
	int GetStageBlock() { return stageBlockNum; }
private:
	void LoadStage();

	void SetFloor(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetBreakBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetWallBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetGoal(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetMoveFloor(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void MoveFloorUpdate(int i);
private:
	const float mapSize = 25.0f;
	const int drawNumX = 10;
	 
	//ブロック
	int	map[MAP_HEIGHT][MAP_WIDTH] = {};		//マップチップ
	int mapPos[MAP_HEIGHT][MAP_WIDTH] = {};

	int mapOBJ[MAP_HEIGHT][MAP_WIDTH] = {};		//壁などのOBJ
	int mapOBJPos[MAP_HEIGHT][MAP_WIDTH] = {};	//壁などのOBJの座標

	//床
	ObjectData floorOBJ;
	std::vector<Floor*>floor;
	int floorGraph = 0;

	//壁OBJ
	ObjectData wallOBJ = {};
	std::vector<WallData*>wallData;
	int wallGraph = 0;
	const Vec3 wallScale = { 25.0f, 70.0f, 25.0f };

	//ゴール
	ObjectData goalOBJ = {};
	std::vector<GoalData*>goalData;
	int goalGraph = 0;
	Vec3 goalScale = { 20.0f,4.0f,20.0f };
	bool goalFlag = false;

	//壊れる箱
	ObjectData breakBoxOBJ = {};
	std::vector<BreakBoxData*>breakBoxData;
	Vec3 breakBoxScale = { 20.0f,20.0f,20.0f };
	int breakBoxGraph = 0;

	
	int stageBlockNum = 0;//ステージにある最大のブロック数
	int blockNum = 0;	//壊したブロック

	//動く床
	ObjectData moveFloorOBJ = {};
	std::vector<MoveFloorData*>moveFloorData;
	int moveGraph = 0;
};