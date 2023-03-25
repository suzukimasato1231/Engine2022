#pragma once
#include<vector>
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
#include<LoadJson.h>
class Player;
/// <summary>
/// �X�e�[�W�N���X
/// </summary>
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
	void Update(const Vec3& pPos);
	//�`��
	void Draw(const Vec3& pPos, bool shadowFlag = false);
	//�p�[�e�B�N���`��
	void DrawParicle();
	//�X�e�[�W�쐬
	void LoadStage(int stageNum);
public://�}�b�v
	inline bool GetClearFlag() { return m_goalFlag; }
	inline int GetBlockNum() { return m_blockNum; }
	inline int GetBlockMax() { return m_blockMax; }
private:
	//��̕`��
	void DrawWater();
	//���锠�̏���
	void BreakBoxs();
	//���֘A��
	bool CheckBoxJudge(StageData* stageData);
	//�u���֘A��
	bool CheckFigurineJudge(StageData* stageData);
	//�X�e�[�W��̒���
	void SetStageBox(StageData* stageData, const Vec3& scale);
	//���̓����蔻��Ƒ����\��
	void FloorHitDropPoint(StageData* s, const Vec3& PPos);
private:
	const float c_mapSize = 25.0f;
	const int c_drawNumY = 35;
private://���֘A
	//��̏�
	ObjectData m_floorOBJ;
	int m_floorGraph = 0;
	//������
	MoveFloor m_moveFloor;

	FloorPitfall m_floorPitfall;
private://㩃u���b�N
	//��OBJ
	int m_wallGraph = 0;
	const Vec3 m_wallScale = { 25.0f, 70.0f, 25.0f };
	//�S�[��
	GoalFish m_goalFish;
	bool m_goalFlag = false;
	//��
	BlockBox m_blockBox;
	const Vec3 boxScale = { 20.0f ,20.0f,20.0f };
	//�d�����
	Electricity m_elect;
	//�댯��
	DangerFish m_dangerFish;
	//�u��
	FigurineOBJ m_figurineOBJ;
private:
	//�󂵂����ɏo�鋛
	FishBox m_fishBox;

	int m_blockMax = 0;	//�X�e�[�W�ɂ���ő�̃u���b�N��
	int m_blockNum = 0;	//�󂵂��u���b�N


	ObjectData m_water = {};
	int m_waterGraph = 0;
	Vec2 m_waterUV = {};

	PSR m_blackPsr[6][4] = {};
	//�����n�_�\���N���X
	DropPoint m_dropPoint;

	BoxStaring m_boxStaring;

	//�T�E���h
	SoundData m_boxSE = {};
	SoundData m_jumpSE = {};
	SoundData m_goalSE = {};
	SoundData m_bombSE = {};
	bool m_goalSEFlag = false;

	std::vector<StageData*>stageData;
	LevelData* levelData = nullptr;
};