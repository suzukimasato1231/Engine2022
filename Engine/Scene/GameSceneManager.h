#pragma once
#include "_DirectX.h"
#include "Safe_delete.h"
#include"DebugText.h"
#include"ParticleManager.h"
#include"Collision.h"
#include"Audio.h"
#include"FBXObject3d.h"
#include"../Player.h"
#include"../PushCollision.h"
#include"../Stage.h"
#include"../UI.h"
#include"../TimeAttack.h"
#include"../EnemyManager.h"
extern const int window_width;
extern const int window_height;
enum ChangeStatus
{
	ChangeClear,
	ChangeRetry,
	ChangeSelect,
};
/// <summary>
/// �Q�[���V�[��
/// </summary>
class GameSceneManager 
{

public:
	GameSceneManager();
	~GameSceneManager();

	void Initialize();

	void Init(int stageNum);

	void Update();

	void Draw();

	void ShadowDraw();

	void Reset(int stageNum);
public:
	bool GetChangeScene() { return changeScene; }

	int GetChangeNum() { return changeNum; }
private:
	LightGroup *lightGroup = nullptr;
	Audio *audio = nullptr;
private://��`
	int stageNum = 1;

	//�X�v���C�g�f�[�^
	SpriteData BGGraph;
	
	Vec2 pos = { 0.0f,0.0f };

	//�V�[�����ς�邩�ǂ���
	bool changeScene = false;
	int changeSceneTime = 100;
	//�Q�[���I�[�o�[��
	int changeNum = 0;
};