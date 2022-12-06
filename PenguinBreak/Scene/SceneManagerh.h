#pragma once
#include"GameSceneManager.h"
#include"TitleScene.h"
#include"StageSelect.h"
#include"ResultScene.h"
#include "ShadowMap.h"
#include<Audio.h>
enum Scene
{
	Title,
	SelectScene,
	GameScene,
	Result,
};

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
	SceneManagerh();
	~SceneManagerh();

	void Initialize();

	void Update();

	void Draw();

	void Delete();
private://定義
	TitleScene titleScene;
	StageSelect stageScene;
	GameSceneManager gameScene;
	ResultScene resultScene;
	int scene = Title;	//シーン管理
	int sceneMe = Title;
	SpriteData changeBlack;
	int changeSceneFlag = false;
	Vec4 changeSceneColor = { 1.0f,1.0f,1.0f,0.0f };//シーンが変わる時の色
	bool Flag = false;

	Audio* audio = nullptr;
	SoundData bgm;
};