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
	//�R���X�g���N�^
	Stage();
	//�f�X�R���X�g���N�^
	~Stage();
	//������
	void Init();
	//�X�e�[�W�I��
	void MainInit(int stageNum);
	//�X�V
	void Update(const Vec3 &pPos);
	//�`��
	void Draw(const Vec3 &pPos, bool shadowFlag = false);

	void DrawParicle();
	//�X�e�[�W�쐬
	void LoadStage(int stageNum);
public://�}�b�v
	bool GetClearFlag() { return goalFlag; }

	int GetBlockNum() { return blockNum; }
	int GetBlockMax() { return blockMax; }
private:
	//��̕`��
	void DrawWater();

	void SetFloor(const Vec3 &position, const Vec3 &scale, const Vec3 &angle, const Vec2 &map, int type, int size = 0);

	void SetBreakBox(const Vec3 &position, const Vec3 &scale, const Vec3 &angle, const Vec2 &map);

	void SetJumpBox(const Vec3 &position, const Vec3 &scale, const Vec3 &angle, const Vec2 &map);

	void SetWallBox(const Vec3 &position, const Vec3 &scale, const Vec3 &angle, const Vec2 &map, int type);

	void SetBreakHard(const Vec3 &position, const Vec3 &scale, const Vec3 &angle, const Vec2& map);

	void SetGoal(const Vec3 &position, const Vec3 &scale, const Vec3 &angle, const Vec2 &map);

	void SetMoveFloor(const Vec3 &position, const Vec3 &scale, const Vec3 &angle, const Vec2 &map);

	void SetMoveFloor2(const Vec3 &position, const Vec3 &scale, const Vec3 &angle, const Vec2 &map);

	void SetPitfallFloor(const Vec3 &position, const Vec3 &scale, const Vec3 &angle, const Vec2 &map, int time);

	void SetElectricity(const Vec3 &position, const Vec3 &scale, const Vec3 &angle, const Vec2 &map);

	void SetFishAttack(const Vec3 &position, const Vec3 &scale, const Vec3 &angle, const Vec2 &map);

	void SetFigrineOBJ(const Vec3 &position, const Vec3 &scale, const Vec3 &angle, const Vec2 &map,int type);
private:
	const float mapSize = 25.0f;
	const int drawNumY = 35;
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
	int wallGraph = 0;
	const Vec3 wallScale = { 25.0f, 70.0f, 25.0f };
	//�S�[��
	GoalFish goalFish;
	bool goalFlag = false;
	//��
	BlockBox blockBox;
	//�d�����
	Electricity elect;
	//�댯��
	DangerFish dangerFish;
	//�u��
	FigurineOBJ figurineOBJ;
private:
	//�󂵂����ɏo�鋛
	FishBox fishBox;

	int blockMax = 0;	//�X�e�[�W�ɂ���ő�̃u���b�N��
	int blockNum = 0;	//�󂵂��u���b�N


	ObjectData water = {};
	int waterGraph = 0;
	Vec2 waterUV = {};

	PSR blackPsr[3] = {};
	//�����n�_�\���N���X
	DropPoint dropPoint;

	BoxStaring boxStaring;

	//�T�E���h
	SoundData boxSE={};
	SoundData jumpSE = {};
	SoundData goalSE = {};
	bool goalSEFlag = false;
};