#pragma once
#include "_DirectX.h"
#include "Safe_delete.h"
#include"DebugText.h"
#include"ParticleManager.h"
#include"Collision.h"
#include"Audio.h"
#include"FBXObject3d.h"
#include"../App/player/Player.h"
#include"../App/stage/PushCollision.h"
#include"../App/stage/Stage.h"
#include"../App/ui/UI.h"
#include"../App/TimeAttack/TimeAttack.h"
#include<memory>
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
	std::unique_ptr<LightGroup>lightGroup;
	std::unique_ptr<Audio> audio;
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

	//�S�[�����̉��o�͂���
	bool goalStagingFlag = false;
	int goalStagingTime = 0;
	const int goalStagingTimeMax = 200;
	//�J�����p�x
	const float cameraAngle = 45.0f;
	const float goalCamraAngleMax = 25.0f;
	float goalCameraAngle = 0.0f;
	//�J��������
	const float goalDistanceMax = 100.0f;
	const float goalDistanceMin = 50.0f;
	float goalDistance = 0.0f;


};