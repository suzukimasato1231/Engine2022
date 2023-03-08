#pragma once
#include<Object.h>
#include "StegeObject.h"
/// <summary>
/// �S�[���N���X
/// </summary>
class GoalFish
{
public:
	//�R���X�g���N�^
	GoalFish();
	//�f�X�R���X�g���N�^
	~GoalFish();
	//������
	void Init();
	//�X�V
	void Update();
	//�`��
	void Draw(StageOBJ* stageObj, const bool shadowFlag);

	Vec3 GetGoalScale() { return m_goalScale; }
private:
	//�S�[��
	ObjectData  m_goalOBJ = {};
	Vec3  m_goalScale = { 20.0f,25.0f,20.0f };
	bool  m_goalFlag = false;

	Vec3  m_angle = { 0.0f,0.0f,0.0f };
};

