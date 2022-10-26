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
	//�R���X�g���N�^
	Stage();
	//�f�X�R���X�g���N�^
	~Stage();
	//������
	void Init();
	//�X�e�[�W�I��
	void MainInit(int stageNum);
	//�X�V
	void Update(Vec3 pPos);
	//�`��
	void Draw(Vec3 pPos, bool shadowFlag = false);

	void DrawParicle();
	//�X�e�[�W�쐬
	void LoadStage(int stageNum);
public://�}�b�v
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
private://���֘A
	//��̏�
	ObjectData floorOBJ;
	std::vector<Floor*>floor;
	int floorGraph = 0;
	//������
	MoveFloor moveFloor;

	FloorPitfall floorPitfall;
private://㩃u���b�N
	std::vector<StageOBJ*>stageObj;
	//��OBJ
	ObjectData wallOBJ = {};
	int wallGraph = 0;
	const Vec3 wallScale = { 25.0f, 70.0f, 25.0f };
	//�S�[��
	ObjectData goalOBJ = {};
	Vec3 goalScale = { 25.0f,25.0f,25.0f };
	bool goalFlag = false;
	//��
	BlockBox blockBox;
	//�d�����
	Electricity elect;
	//�댯��
	DangerFish dangerFish;
private:
	//�󂵂����ɏo�鋛
	FishBox fishBox;

	int blockMax = 0;//�X�e�[�W�ɂ���ő�̃u���b�N��
	int blockNum = 0;	//�󂵂��u���b�N


	ObjectData blackGround = {};
	int blackGraph = 0;
	PSR blackPsr[3] = {};
};