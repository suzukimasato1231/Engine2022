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

	bool selectFlag = false;			//���̃V�[���ֈړ�
	
	ObjectData selectOBJ;				//�Z���N�g������OBJ
	int selectGraph[stageNumMax];		//�Z���N�gOBJ�̉摜
	const float selectScale = 10.0f;			//�Z���N�gOBJ�̑傫��
	Vec3 selectPos[stageNumMax];		//�Z���N�gOBJ�̍��W
	Box selectBox[stageNumMax];			//�Z���N�gOBJ��BOX
	PSR selectPsr[stageNumMax];			//�Z���N�gOBJ��PSR

	int stageNum = 0;					//���݂̃X�e�[�W

	//���o
	bool productionFlag[3] = {};
	const int productionTimeMax = 30;
	int productionTime = 0;


};


