#pragma once
#include"Vec.h"
#include"Object.h"
#include<vector>
#include <CollisionPrimitive.h>
#include <LoadCSV.h>
class Player;


enum StageFloor
{
	NoneFloor,
	FloorNormal,
	Floor169,
	Floor11,
};

enum StageOBJ
{
	NoneOBJ,
	Wall,
	Goal,
	BreakBox,
};

class Stage
{
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

	//Vec2 GetMapSize() { return mapSize; }

	bool GetClearFlag() { return goalFlag; }
private:
	const float mapSize = 25.0f;

	//ブロック
	int	map[MAP_HEIGHT][MAP_WIDTH] = {};		//マップチップ
	int mapPos[MAP_HEIGHT][MAP_WIDTH] = {};

	int mapOBJ[MAP_HEIGHT][MAP_WIDTH] = {};		//壁などのOBJ
	int mapOBJPos[MAP_HEIGHT][MAP_WIDTH] = {};	//壁などのOBJの座標
	//床
	ObjectData floorOBJ[3];
	int floorGraph = 0;

	//壁OBJ
	ObjectData wallOBJ = {};
	int wallGraph = 0;
	const Vec3 wallScale = { 25.0f, 50.0f, 25.0f };

	//ゴール
	ObjectData goalOBJ = {};
	int goalGraph = 0;
	Vec3 goalPos = {};
	Vec3 goalScale = { 20.0f,2.0f,20.0f };
	Box goalBox = {};
	bool goalFlag = false;

	//壊れる箱
	ObjectData breakBoxOBJ = {};
	int breakBoxGraph = 0;
	Box breakBox = {};
	Vec3 breakBoxScale = { 20.0f,20.0f,20.0f };
};