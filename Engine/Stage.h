#pragma once
#include"Vec.h"
#include"Object.h"
#include<vector>
#include <CollisionPrimitive.h>
#include <LoadCSV.h>
class Player;
/// <summary>
/// 床
/// </summary>
struct Floor
{
	Box box = {};
	Vec3 position{};
	Vec3 scale = {};
	Vec3 angle = {};

};
/// <summary>
/// ボックス
/// </summary>
struct Block
{
	Box box = {};
	Vec3 position{};
	Vec3 scale = {};
	Vec3 angle = {};
};

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
private:
	void SetFloor(Vec3 position, Vec3 scale, Vec3 angle);

	void SetBlock(Vec3 position, Vec3 scale);
public://マップ
	int GetMap(int i, int j) { return map[j][i]; }

	Vec2 GetMapSize() { return mapSize; }
public://床
	Box GetFloorBox(int i) { if (floor.size() > 0) { return floor[i]->box; } }

	Vec3 GetFloorPos(int i) { if (floor.size() > 0) { return floor[i]->position; } return Vec3{}; }

	Vec3 GetFloorAngle(int i) { if (floor.size() > 0) { return floor[i]->angle; }return Vec3{}; }

	Vec3 GetFloorScale(int i) { if (floor.size() > 0) { return floor[i]->scale; }return Vec3{}; }

	int GetFloorSize() { return  static_cast<int>(floor.size()); };
public://ボックス
	Box GetBlockBlock(int i) { if (block.size() > 0) { return block[i]->box; } return Box{}; }

	Vec3 GetBlockPos(int i) { if (block.size() > 0) { return block[i]->position; }return Vec3{}; }

	Vec3 GetBlockAngle(int i) { if (block.size() > 0) { return block[i]->angle; }return Vec3{}; }

	Vec3 GetBlockScale(int i) { if (block.size() > 0) { return block[i]->scale; } return Vec3{}; }

	int GetBlockSize() { return static_cast<int>(block.size()); };
private:
	const Vec2 mapSize = { 50.0f,50.0f };
	//床
	std::vector<Floor*> floor;
	int floorGraph = 0;
	//ブロック
	std::vector<Block*>block;

	int	map[MAP_HEIGHT][MAP_WIDTH] = {};//マップチップ
	int mapPos[MAP_HEIGHT][MAP_WIDTH] = {};

	int mapOBJ[MAP_HEIGHT][MAP_WIDTH] = {};		//壁などのOBJ
	int mapOBJPos[MAP_HEIGHT][MAP_WIDTH] = {};	//壁などのOBJの座標
	//床
	ObjectData floorOBJ[3];

	//壁OBJ
	ObjectData wallOBJ = {};
	int wallGraph = 0;
	const Vec3 wallScale = { 50.0f, 50.0f, 50.0f };

	//ゴール
	ObjectData goalOBJ = {};
	int goalGraph = 0;
	Vec3 goalPos = {};
	Sphere goalSphere = {};
};