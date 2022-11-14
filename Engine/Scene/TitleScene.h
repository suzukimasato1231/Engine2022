#pragma once
#include "_DirectX.h"
#include"DebugText.h"
#include"Collision.h"
#include"Audio.h"
#include"FBXObject3d.h"
#include"Object.h"
#include"Sprite.h"
#include<memory>
extern const int window_width;
extern const int window_height;
class TitleScene 
{
public:
	TitleScene();
	~TitleScene();

	void Initialize();

	void Init();

	void Update();

	void Draw();

	void ShadowDraw();
private:
	std::unique_ptr<LightGroup>lightGroup;
private://’è‹`
	ObjectData titlePlayer;
	PSR titlePsr = {};
	ObjectData box;
	PSR boxPsr = {};
	int boxGraph;

	ObjectData wallObj;
	PSR wallPsr;

	ObjectData floorObj;

	//UI
	SpriteData titleGraph;
	SpriteData titleButtonGraph;
	int buttonTime = 0;
};


