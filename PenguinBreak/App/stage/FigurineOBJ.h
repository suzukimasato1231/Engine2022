#pragma once
#include "StegeObject.h"
/// <summary>
/// �u����OBJ
/// </summary>
class FigurineOBJ
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	FigurineOBJ();
	//�f�X�R���X�g���N�^
	~FigurineOBJ();
	/// <summary>
	/// ������
	/// </summary>
	void Init();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="stageObj">�X�e�[�W�f�[�^</param>
	/// <param name="shadowFlag">�e�t���O</param>
	void Draw(StageData* stageObj, const bool shadowFlag);
private:
	//��OBJ
	ObjectData m_wallOBJ;
	//�͂��OBJ
	ObjectData m_deadTree;
	//��
	ObjectData m_stone;
	//�X�̃A�[�`
	ObjectData m_iceArch;
	//�Ŕ�
	ObjectData m_signboard;
	TextureData m_tutorialGraph[2] = {};
	int m_tutorialNum = SIGNBOARD1;		//�`���[�g���A���̊�{�l

};

