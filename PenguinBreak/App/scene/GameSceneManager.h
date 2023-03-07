#pragma once
#include "_DirectX.h"
#include"DebugText.h"
#include"ParticleManager.h"
#include"../App/player/Player.h"
#include"../App/stage/Stage.h"
#include"../App/ui/UI.h"
#include"../App/player/DecLifeStaging.h"
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
private:
	//�Q�[���I�[�o�[�Z���N�g
	enum GameOverSelect
	{
		GameOverSelect = 1,
		GameOverRetry,
	};
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameSceneManager();
	/// <summary>
	/// �f�X�R���X�g���N�^
	/// </summary>
	~GameSceneManager();
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	void Init(int stageNum);
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	/// <summary>
	/// �e�`��
	/// </summary>
	void ShadowDraw();
	/// <summary>
	/// 
	/// </summary>
	void SecondDraw();
	/// <summary>
	/// ���Z�b�g
	/// </summary>
	/// <param name="stageNum">�X�e�[�W</param>
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
	//�Q�[���I�[�o�[��
	int changeNum = 0;

	//�S�[�����̉��o�͂���
	bool goalStagingFlag = false;
	int goalStagingTime = 0;
	const int goalStagingTimeMax = 260;

	//�J�����p�x
	const float cameraAngle = 37.5f;
	const float goalCamraAngleMax = 25.0f;
	float goalCameraAngle = 0.0f;
	//�J��������
	const float goalDistanceMax = 100.0f;
	const float goalDistanceMin = 50.0f;
	float goalDistance = 0.0f;
	//UI�N���X
	UI ui;
	//���S���̉��o�N���X
	DecLifeStaging decLifeStaging;

	//���f�[�^
	SoundData decisionSE = {};
	SoundData selectSE = {};
};