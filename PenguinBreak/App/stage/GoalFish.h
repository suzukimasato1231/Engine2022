#pragma once
#include<Object.h>
#include "StegeObject.h"
/// <summary>
/// �S�[���N���X
/// </summary>
class GoalFish
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GoalFish();
	/// <summary>
	/// �f�X�R���X�g���N�^
	/// </summary>
	~GoalFish();
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

	Vec3 GetGoalScale() { return m_goalScale; }
private:
	//�S�[��
	ObjectData  m_goalOBJ = {};					//���F��OBJ
	Vec3  m_goalScale = { 20.0f,25.0f,20.0f };	//���̃T�C�Y
	const Vec3 c_OBJScale = { 3.0f,3.0f,3.0f };	//OBJ�̊g�吔
	bool  m_goalFlag = false;					//�S�[���������̃t���O
	Vec3 m_goalAngle = { 0.0f,0.0f,180.0f };	//���̊p�x
	const float c_angleSpeed = 1.0f;			//�p�x���ς��X�s�[�h
	const float c_angleMax = 360.0f;			//�p�x�̍ő�
};

