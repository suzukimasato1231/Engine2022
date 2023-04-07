#pragma once
#include"GameScene.h"
#include"TitleScene.h"
#include"StageSelect.h"
#include"ResultScene.h"
#include "ShadowMap.h"

extern const int window_width;
extern const int window_height;
class SceneManager :public Singleton<SceneManager>
{
private:
	friend Singleton<SceneManager>;
	/// <summary>
	/// �V�[���^�C�v
	/// </summary>
	enum Scene
	{
		Title,
		SelectScene,
		GameScene,
		Result,
	};
	/// <summary>
	/// �V�[���`�F���W��
	/// </summary>
	enum ChangeNumber
	{
		ChangeStand,
		ChangeFirst,
		ChangeEnd,
	};
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SceneManager();
	/// <summary>
	/// �f�X�R���X�g���N�^
	/// </summary>
	~SceneManager();
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	/// <summary>
	/// �폜
	/// </summary>
	void Delete();
private:
	/// <summary>
	/// �V�[���`�F���W�̏���
	/// </summary>
	void SceneChange();
private://��`
	TitleScene  m_titleScene;
	StageSelect  m_stageScene;
	GameSceneManager  m_gameScene;
	ResultScene  m_resultScene;
	int  m_scene = Title;	//�V�[���Ǘ�
	int  m_sceneMe = Title;
	SpriteData  m_changeBlack;
	int  m_changeSceneFlag = false;
	Vec4  m_changeSceneColor = { 1.0f,1.0f,1.0f,0.0f };//�V�[�����ς�鎞�̐F
	bool  m_Flag = false;

	Audio* m_audio = nullptr;
	SoundData  m_bgm={};
	SoundData  m_buttonSE={};

	ShadowMap  m_shadowMapFar;
};