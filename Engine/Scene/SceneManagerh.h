#pragma once
#include"GameSceneManager.h"
#include"TitleScene.h"
#include"PostEffect.h"
enum Scene
{
	Title,
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
private://��`
	PostEffect* postEffect = nullptr;
	//�V�[���Ǘ�
	int scene = Title;
};