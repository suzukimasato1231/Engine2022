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
#include"../UI.h"
#include"../TimeAttack.h"
extern const int window_width;
extern const int window_height;
class GameSceneManager 
{

public:
	GameSceneManager();
	~GameSceneManager();

	void Initialize();

	void Init(int stageNum);

	void Update();

	void Draw();

	void Reset(int stageNum);
public:
	bool GetChangeScene() { return changeScene; }
private:
	LightGroup *lightGroup = nullptr;
	Audio *audio = nullptr;
private://定義
	int stageNum = 1;

	//スプライトデータ
	SpriteData BGGraph;
	
	Vec2 pos = { 0.0f,0.0f };

	//FBX
	Model *model1 = nullptr;
	FBXObject3d *fbxObject1 = nullptr;

	//シーンが変わるかどうか
	bool changeScene = false;
};