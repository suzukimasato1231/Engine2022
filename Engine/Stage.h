#pragma once
#include"Object.h"
#include<vector>
#include <LoadCSV.h>
#include"./StegeObject.h"
#include"../Engine/EnemyManager.h"
class Player;
class Stage :public Singleton<Stage>
{
private:
	friend Singleton<Stage>;
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
	void Draw(bool shadowFlag = false);

	void LoadStage(int stageNum);
public://�}�b�v
	int GetMap(int i, int j) { return map[j][i]; }

	bool GetClearFlag() { return goalFlag; }

	int GetBlockNum() { return blockNum; }
	int GetStageBlock() { return stageBlockNum; }
private:

	void SetFloor(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetBreakBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetJumpBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetWallBox(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetBreakHard(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetGoal(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void SetMoveFloor(Vec3 position, Vec3 scale, Vec3 angle, Vec2 map);

	void MoveFloorUpdate(int i);
private:
	const float mapSize = 25.0f;
	const int drawNumX = 10;
	const int drawNumY = 35;
	//�u���b�N
	int	map[MAP_HEIGHT][MAP_WIDTH] = {};		//�}�b�v�`�b�v
	int mapPos[MAP_HEIGHT][MAP_WIDTH] = {};

	int mapOBJ[MAP_HEIGHT][MAP_WIDTH] = {};		//�ǂȂǂ�OBJ
	int mapOBJPos[MAP_HEIGHT][MAP_WIDTH] = {};	//�ǂȂǂ�OBJ�̍��W

	//��
	ObjectData floorOBJ;
	std::vector<Floor*>floor;
	int floorGraph = 0;

	int mask = 0;
	int green = 0;
	int grn = 0;

	std::vector<StageOBJ*>stageObj;
	//��OBJ
	ObjectData wallOBJ = {};
	int wallGraph = 0;
	const Vec3 wallScale = { 25.0f, 70.0f, 25.0f };
	//�S�[��
	ObjectData goalOBJ = {};
	Vec3 goalScale = { 25.0f,25.0f,25.0f };
	bool goalFlag = false;
	//���锠
	ObjectData breakBoxOBJ = {};
	Vec3 breakBoxScale = { 20.0f,20.0f,20.0f };
	int normalBoxGraph = 0;
	int breakBoxGraph = 0;


	int stageBlockNum = 0;//�X�e�[�W�ɂ���ő�̃u���b�N��
	int blockNum = 0;	//�󂵂��u���b�N

	//������
	ObjectData moveFloorOBJ = {};
	std::vector<MoveFloorData*>moveFloorData;
	int moveGraph = 0;
};