#pragma once
#include"Vec.h"
#include"Object.h"
#include<vector>
#include <CollisionPrimitive.h>
#include <LoadCSV.h>
class Player;
/// <summary>
/// ��
/// </summary>
struct Floor
{
	Box box = {};
	Vec3 position{};
	Vec3 scale = {};
	Vec3 angle = {};

};
/// <summary>
/// �{�b�N�X
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
	//�R���X�g���N�^
	Stage();
	//�f�X�R���X�g���N�^
	~Stage();
	//������
	void Init();
	//�X�e�[�W�I��
	void MainInit(int stageNum);
	//�X�V
	void Update();
	//�`��
	void Draw();
private:
	void SetFloor(Vec3 position, Vec3 scale, Vec3 angle);

	void SetBlock(Vec3 position, Vec3 scale);
public://�}�b�v
	int GetMap(int i, int j) { return map[j][i]; }

	Vec2 GetMapSize() { return mapSize; }
public://��
	Box GetFloorBox(int i) { if (floor.size() > 0) { return floor[i]->box; } }

	Vec3 GetFloorPos(int i) { if (floor.size() > 0) { return floor[i]->position; } return Vec3{}; }

	Vec3 GetFloorAngle(int i) { if (floor.size() > 0) { return floor[i]->angle; }return Vec3{}; }

	Vec3 GetFloorScale(int i) { if (floor.size() > 0) { return floor[i]->scale; }return Vec3{}; }

	int GetFloorSize() { return  static_cast<int>(floor.size()); };
public://�{�b�N�X
	Box GetBlockBlock(int i) { if (block.size() > 0) { return block[i]->box; } return Box{}; }

	Vec3 GetBlockPos(int i) { if (block.size() > 0) { return block[i]->position; }return Vec3{}; }

	Vec3 GetBlockAngle(int i) { if (block.size() > 0) { return block[i]->angle; }return Vec3{}; }

	Vec3 GetBlockScale(int i) { if (block.size() > 0) { return block[i]->scale; } return Vec3{}; }

	int GetBlockSize() { return static_cast<int>(block.size()); };
private:
	const Vec2 mapSize = { 50.0f,50.0f };
	//��
	std::vector<Floor*> floor;
	int floorGraph = 0;
	//�u���b�N
	std::vector<Block*>block;

	int	map[MAP_HEIGHT][MAP_WIDTH] = {};//�}�b�v�`�b�v
	int mapPos[MAP_HEIGHT][MAP_WIDTH] = {};

	int mapOBJ[MAP_HEIGHT][MAP_WIDTH] = {};		//�ǂȂǂ�OBJ
	int mapOBJPos[MAP_HEIGHT][MAP_WIDTH] = {};	//�ǂȂǂ�OBJ�̍��W
	//��
	ObjectData floorOBJ[3];

	//��OBJ
	ObjectData wallOBJ = {};
	int wallGraph = 0;
	const Vec3 wallScale = { 50.0f, 50.0f, 50.0f };

	//�S�[��
	ObjectData goalOBJ = {};
	int goalGraph = 0;
	Vec3 goalPos = {};
	Sphere goalSphere = {};
};