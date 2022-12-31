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

	Vec3 GetGoalScale() { return goalScale; }
private:
	//�S�[��
	ObjectData goalOBJ = {};
	Vec3 goalScale = { 20.0f,25.0f,20.0f };
	bool goalFlag = false;

	Vec3 angle = { 0.0f,0.0f,0.0f };
};

