#pragma once
#include"Sprite.h"
class UI
{

public:
	UI();
	~UI();

	void Init();

	void Update(int fishNum);

	void Draw(int pLives, bool gameoverFlag, int gameoverNum = 0);

private:
	SpriteData boxGraph;

	SpriteData playerIcon;

	SpriteData fishGraph;

	SpriteData uiNumber[10];
	SpriteData uiSlash;
	//ゲームオーバー時の
	SpriteData gameoverGraph;
	SpriteData selectGraph;


	//演出
	float fishPosPlas = 0.0f;
	const int stagingTimeMax = 20;
	const float stagingScaleMax = 1.5f;
	float stagingScale[4] = {0.0f,0.0f,0.0f,0.0f};
	int stagingTime[4] = {};
	bool stagingFlag[4] = {};
	//壊した箱の数
	int breakNumber = 1, breakRemain = 1;
	//最大箱の数
	int breakNumberMax = 1, breakRemainMax = 1;
	//魚の数
	int fishNumber = 1, fishRemain = 1;
};

