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
public://�}�b�v
	int GetMap(int i, int j) { return map[j][i]; }

	//Vec2 GetMapSize() { return mapSize; }

	bool GetClearFlag() { return goalFlag; }
private:
	const float mapSize = 25.0f;

	//�u���b�N
	int	map[MAP_HEIGHT][MAP_WIDTH] = {};		//�}�b�v�`�b�v
	int mapPos[MAP_HEIGHT][MAP_WIDTH] = {};

	int mapOBJ[MAP_HEIGHT][MAP_WIDTH] = {};		//�ǂȂǂ�OBJ
	int mapOBJPos[MAP_HEIGHT][MAP_WIDTH] = {};	//�ǂȂǂ�OBJ�̍��W
	//��
	ObjectData floorOBJ[3];
	int floorGraph = 0;

	//��OBJ
	ObjectData wallOBJ = {};
	int wallGraph = 0;
	const Vec3 wallScale = { 25.0f, 50.0f, 25.0f };

	//�S�[��
	ObjectData goalOBJ = {};
	int goalGraph = 0;
	Vec3 goalPos = {};
	Vec3 goalScale = { 20.0f,2.0f,20.0f };
	Box goalBox = {};
	bool goalFlag = false;

	//���锠
	ObjectData breakBoxOBJ = {};
	int breakBoxGraph = 0;
	Box breakBox = {};
	Vec3 breakBoxScale = { 20.0f,20.0f,20.0f };
};