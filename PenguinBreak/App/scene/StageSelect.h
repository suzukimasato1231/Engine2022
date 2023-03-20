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

	void StagePlas() { m_stageNum++; }

	void SetBreakBoxNum(int breakBox_);
public:
	std::unique_ptr<LightGroup>lightGroup;
public:
	int GetStageNum() { return  m_stageNum; }

	bool GetSelectFlag() { return  m_selectFlag; }
private://��`
	static const int c_stageNumMax = 3;	//�ő�X�e�[�W��

	bool  m_selectFlag = false;			//���̃V�[���ֈړ�

	ObjectData  m_selectOBJ;				//�Z���N�g������OBJ
	int  m_selectGraph[c_stageNumMax];		//�Z���N�gOBJ�̉摜
	const float c_selectScale = 10.0f;	//�Z���N�gOBJ�̑傫��
	Vec3  m_selectPos[c_stageNumMax];		//�Z���N�gOBJ�̍��W
	Box  m_selectBox[c_stageNumMax];			//�Z���N�gOBJ��BOX
	PSR  m_selectPsr[c_stageNumMax];			//�Z���N�gOBJ��PSR

	//�X�e�[�W���Ƃ̔��̉󂵂���
	ObjectData  m_boxBreakOBJ = {};		//�󂵂����̐���\������
	ObjectData  m_flameOBJ = {};			//�t���[��
	PSR  m_boxBreakPSR[c_stageNumMax] = {};	//�󂵂�����PSR�ۑ�
	PSR  m_flamePSR[c_stageNumMax] = {};		//�t���[��PSR
	int  m_boxBreakGraph = 0;				//�󂵂����̉摜
	int  m_boxFramGraph = 0;
	int  m_numberGraph[11] = {};			//�����̉摜

	//�󂵂�����ۑ�����p
	const int c_breakBoxMax[c_stageNumMax] = { 9,11,10 };
	int  m_breakNumMax[c_stageNumMax] = { 0,0,0 };
	int  m_breakNumTenMax[c_stageNumMax] = { 0,0,0 };

	int  m_breakBox[c_stageNumMax] = { 0,0,0 };
	int  m_breakNum[c_stageNumMax] = { 0,0,0 };
	int  m_breakNumTen[c_stageNumMax] = { 0,0,0 };

	int  m_stageNum = 0;					//���݂̃X�e�[�W

	//���o
	bool  m_productionFlag[3] = {};
	const int c_productionTimeMax = 30;
	int  m_productionTime = 0;

	SoundData  m_boxSE = {};
};

