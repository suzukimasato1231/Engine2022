#pragma once
#include "_DirectX.h"
#include "Safe_delete.h"
#include"Collision.h"
#include"Audio.h"
#include"FBXObject3d.h"
#include"Object.h"
#include<memory>
extern const int window_width;
extern const int window_height;
/// <summary>
/// �X�e�[�W�Z���N�g
/// </summary>
class StageSelect
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	StageSelect();
	/// <summary>
	/// �f�X�R���X�g���N�^
	/// </summary>
	~StageSelect();
	//������
	void Initialize();
	/// <summary>
	/// ���������[�v
	/// </summary>
	void Init();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	/// <summary>
	/// �e�̕`��
	/// </summary>
	void DrawShadow();

	void StagePlas() { stageNum++; }

	void SetBreakBoxNum(int breakBox_);
public:
	std::unique_ptr<LightGroup>lightGroup;
public:
	int GetStageNum() { return stageNum; }

	bool GetSelectFlag() { return selectFlag; }
private://��`
	static const int stageNumMax = 3;	//�ő�X�e�[�W��

	bool selectFlag = false;			//���̃V�[���ֈړ�

	ObjectData selectOBJ;				//�Z���N�g������OBJ
	int selectGraph[stageNumMax];		//�Z���N�gOBJ�̉摜
	const float selectScale = 10.0f;	//�Z���N�gOBJ�̑傫��
	Vec3 selectPos[stageNumMax];		//�Z���N�gOBJ�̍��W
	Box selectBox[stageNumMax];			//�Z���N�gOBJ��BOX
	PSR selectPsr[stageNumMax];			//�Z���N�gOBJ��PSR

	//�X�e�[�W���Ƃ̔��̉󂵂���
	ObjectData boxBreakOBJ = {};		//�󂵂����̐���\������
	ObjectData flameOBJ = {};			//�t���[��
	PSR boxBreakPSR[stageNumMax] = {};	//�󂵂�����PSR�ۑ�
	PSR flamePSR[stageNumMax] = {};		//�t���[��PSR
	int boxBreakGraph = 0;				//�󂵂����̉摜
	int boxFramGraph = 0;
	int numberGraph[11] = {};			//�����̉摜

	//�󂵂�����ۑ�����p
	const int breakBoxMax[3] = { 10,10,10 };
	int breakNumMax[3] = { 0,0,0 };
	int breakNumTenMax[3] = { 0,0,0 };

	int breakBox[3] = { 0,0,0 };
	int breakNum[3] = { 0,0,0 };
	int breakNumTen[3] = { 0,0,0 };


	int stageNum = 0;					//���݂̃X�e�[�W

	//���o
	bool productionFlag[3] = {};
	const int productionTimeMax = 30;
	int productionTime = 0;

	SoundData boxSE = {};
};


