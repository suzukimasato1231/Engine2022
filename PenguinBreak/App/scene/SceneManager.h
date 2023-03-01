#pragma once
#include"GameSceneManager.h"
#include"TitleScene.h"
#include"StageSelect.h"
#include"ResultScene.h"
#include "ShadowMap.h"
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

extern const int window_width;
extern const int window_height;
class SceneManagerh :public Singleton<SceneManagerh>
{
private:
	friend Singleton<SceneManagerh>;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SceneManagerh();
	/// <summary>
	/// �f�X�R���X�g���N�^
	/// </summary>
	~SceneManagerh();
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
	TitleScene titleScene;
	StageSelect stageScene;
	GameSceneManager gameScene;
	ResultScene resultScene;
	int scene = Title;	//�V�[���Ǘ�
	int sceneMe = Title;
	SpriteData changeBlack;
	int changeSceneFlag = false;
	Vec4 changeSceneColor = { 1.0f,1.0f,1.0f,0.0f };//�V�[�����ς�鎞�̐F
	bool Flag = false;

	Audio* audio = nullptr;
	SoundData bgm={};
	SoundData buttonSE={};

	ShadowMap shadowMapFar;
};