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
class TitleScene :public Singleton<TitleScene>
{
private:
	friend Singleton<TitleScene>;
public:
	TitleScene();
	~TitleScene();

	void Initialize();

	void Init();

	void Update();

	void Draw();
private:
	Camera* camera = nullptr;
	LightGroup* lightGroup = nullptr;
	Audio* audio = nullptr;
private://’è‹`


};


