#pragma once
#include "DirectXBase.h"
#include "Safe_delete.h"
#include"Collision.h"
#include"Audio.h"
#include"FBXObject3d.h"
#include"Object.h"
#include<memory>
#include"BaseScene.h"
extern const int window_width;
extern const int window_height;
/// <summary>
/// �X�e�[�W�Z���N�g
/// </summary>
class StageSelect:public BaseScene
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
	/// <summary>
	/// ���������[�v
	/// </summary>
	void Init(int stageNum)override;
	/// <summary>
	/// �X�V
	/// </summary>
	void Update(int& stageNum,const int m_breakBox[])override;
	/// <summary>
	/// �`��
	/// </summary>
	void Draw(const int stageNum)override;
	/// <summary>
	/// �e�̕`��
	/// </summary>
	void ShadowDraw()override;
	/// <summary>
	/// 
	/// </summary>
	void SecondDraw()override;

	void Finalize()override;

	void SetBreakBoxNum(int breakBox_);
public:
	std::unique_ptr<LightGroup>lightGroup;
private://��`
	static const int c_stageNumMax = 3;	   //�ő�X�e�[�W��
	
	ObjectData  m_selectOBJ;				//�Z���N�g������OBJ
	int  m_selectGraph[c_stageNumMax];		//�Z���N�gOBJ�̉摜
	const float c_selectScale = 10.0f;	    //�Z���N�gOBJ�̑傫��
	Vec3  m_selectPos[c_stageNumMax];		//�Z���N�gOBJ�̍��W
	Box  m_selectBox[c_stageNumMax];		//�Z���N�gOBJ��BOX
	PSR  m_selectPsr[c_stageNumMax];		//�Z���N�gOBJ��PSR

	//�X�e�[�W���Ƃ̔��̉󂵂���
	ObjectData  m_boxBreakOBJ = {};		    //�󂵂����̐���\������
	ObjectData  m_flameOBJ = {};			//�t���[��
	PSR  m_boxBreakPSR[c_stageNumMax] = {};	//�󂵂�����PSR�ۑ�
	PSR  m_flamePSR[c_stageNumMax] = {};	//�t���[��PSR
	int  m_boxBreakGraph = 0;				//�󂵂����̉摜
	int  m_boxFramGraph = 0;
	int  m_numberGraph[11] = {};			//�����̉摜
	const Vec3 c_numberScale = { 0.3f,0.3f,0.3f };//�����̑傫��
	const Vec3 c_numberAngle = {};                //�����̊p�x

	//�󂵂�����ۑ�����p
	const int c_breakBoxMax[c_stageNumMax] = { 9,11,10 };
	int  m_breakNumMax[c_stageNumMax] = { 0,0,0 };
	int  m_breakNumTenMax[c_stageNumMax] = { 0,0,0 };

	int  m_breakNum[c_stageNumMax] = { 0,0,0 };
	int  m_breakNumTen[c_stageNumMax] = { 0,0,0 };


	//���o
	bool  m_productionFlag[3] = {};
	const int c_productionTimeMax = 30;
	int  m_productionTime = 0;

	SoundData  m_boxSE = {};
};