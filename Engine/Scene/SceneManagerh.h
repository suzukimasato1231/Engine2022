#pragma once
#include"GameSceneManager.h"
#include"TitleScene.h"
#include"StageSelect.h"
#include"ResultScene.h"
#include "../ShadowMap.h"

enum Scene
{
	Title,
	SelectScene,
	GameScene,
	Result,
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
private://íËã`
	TitleScene titleScene;
	StageSelect stageScene;
	GameSceneManager gameScene;
	ResultScene resultScene;
	ShadowMap* shadow = nullptr;
	int scene = Title;	//ÉVÅ[Éìä«óù
};