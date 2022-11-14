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
class StageSelect 
{

public:
	StageSelect();
	~StageSelect();
	//������
	void Initialize();

	void Init();
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�e�̕`��
	void DrawShadow();
public:
	std::unique_ptr<LightGroup>lightGroup;
public:
	int GetStageNum() { return stageNum; }

	bool GetSelectFlag() { return selectFlag; }
private://��`
	static const int stageNumMax = 3;	//�ő�X�e�[�W��

	bool selectFlag = false;

	ObjectData selectOBJ;
	int selectGraph[stageNumMax];
	float selectScale = 10.0f;
	Vec3 selectPos[stageNumMax];
	Box selectBox[stageNumMax];
	PSR selectPsr[stageNumMax];

	int stageNum = 0;			//���݂̃X�e�[�W
};


