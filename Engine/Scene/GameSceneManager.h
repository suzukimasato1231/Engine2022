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
#include"../Enemy.h"
#include"../Stage.h"

extern const int window_width;
extern const int window_height;
class GameSceneManager :public Singleton<GameSceneManager>
{
private:
	friend Singleton<GameSceneManager>;
public:
	GameSceneManager();
	~GameSceneManager();

	void Initialize();

	void Init();

	void Update();

	void Draw();

	void Reset();
public:
	bool GetChangeScene() { return changeScene; }
private:
	Camera *camera = nullptr;
	LightGroup *lightGroup = nullptr;
	Audio *audio = nullptr;
private://定義
	//スプライトデータ
	SpriteData BGGraph;
	
	Vec2 pos = { 0.0f,0.0f };

	//エネミー
	Enemy *enemy = nullptr;

	//FBX
	Model *model1 = nullptr;
	FBXObject3d *fbxObject1 = nullptr;

	//シーンが変わるかどうか
	bool changeScene = false;
};