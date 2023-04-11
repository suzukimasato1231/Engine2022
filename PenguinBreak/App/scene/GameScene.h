#pragma once
#include "DirectXBase.h"
#include"DebugText.h"
#include"ParticleManager.h"
#include"../App/player/Player.h"
#include"../App/stage/Stage.h"
#include"../App/ui/UI.h"
#include"../App/player/DecLifeStaging.h"
#include<memory>
#include"BaseScene.h"
extern const int window_width;
extern const int window_height;
enum class ChangeStatus
{
	ChangeClear,
	ChangeRetry,
	ChangeSelect,
};
/// <summary>
/// �Q�[���V�[��
/// </summary>
class GameScene:public BaseScene
{
private:
	//�Q�[���I�[�o�[�Z���N�g
	enum GameOverSelect
	{
		GameOverRetry = 1,
		GameOverSelect,
	};
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameScene();
	/// <summary>
	/// �f�X�R���X�g���N�^
	/// </summary>
	~GameScene();
	void Init(int stageNum)override;
	/// <summary>
	/// �X�V
	/// </summary>
	void Update(int& stageNum, const int m_breakBox[])override;
	/// <summary>
	/// �`��
	/// </summary>
	void Draw(const int stageNum)override;
	/// <summary>
	/// �e�`��
	/// </summary>
	void ShadowDraw()override;
	/// <summary>
	/// 
	/// </summary>
	void SecondDraw()override;
	

	void Finalize()override;
private:
	/// <summary>
	/// ���Z�b�g
	/// </summary>
	/// <param name="stageNum">�X�e�[�W</param>
	void Reset(int stageNum);
private:
	std::unique_ptr<LightGroup>lightGroup;
	std::unique_ptr<Audio> audio;
private://��`
	int  m_stageNum = 1;

	//�X�v���C�g�f�[�^
	SpriteData  m_BGGraph;
	Vec2  m_pos = { 0.0f,0.0f };

	//�S�[�����̉��o�͂���
	bool  m_goalStagingFlag = false;
	int  m_goalStagingTime = 0;
	const int c_goalStagingTimeMax = 260;

	//�J�����p�x
	const float c_cameraAngle = 37.5f;
	const float c_goalCamraAngleMax = 25.0f;
	float  m_goalCameraAngle = 0.0f;
	const float c_cameraSpeed = 1.0f;       //�J�����̕ς��X�s�[�h
	//�J��������
	const float c_goalDistanceMax = 100.0f;
	const float c_goalDistanceMin = 50.0f;
	float  m_goalDistance = 0.0f;
	//UI�N���X
	UI  m_ui;
	//���S���̉��o�N���X
	DecLifeStaging  m_decLifeStaging;

	//���f�[�^
	SoundData  m_decisionSE = {};
	SoundData  m_selectSE = {};
};