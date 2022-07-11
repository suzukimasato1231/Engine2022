#pragma once
#include"GameSceneManager.h"
#include"TitleScene.h"
#include"StageSelect.h"
enum Scene
{
	Title,
	SelectScene,
	GameScene,
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
private://定義
	
	int scene = Title;	//シーン管理
};