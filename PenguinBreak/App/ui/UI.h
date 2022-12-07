#pragma once
#include"Menu.h"
//UIクラス
class UI
{

public:
	UI();
	~UI();

	void Init();

	void Update(int fishNum, bool& changeScene, int& sceneNum);

	void Draw(const int pLives, const  bool gameoverFlag);

	void Reset();

	bool GetMenuFlag() { return menuFlag; }
private:
	//ゲーム画面UI
	SpriteData boxGraph;

	SpriteData playerIcon;

	SpriteData fishGraph;

	SpriteData uiNumber[10];
	SpriteData uiSlash;

	//メニュー
	Menu menu;
	bool menuFlag = false;

	//演出(ゲーム画面)
	float fishPosPlas = 0.0f;
	const int stagingTimeMax = 20;
	const float stagingScaleMax = 1.5f;
	float stagingScale[4] = { 0.0f,0.0f,0.0f,0.0f };
	int stagingTime[4] = {};
	bool stagingFlag[4] = {};
	//壊した箱の数
	int breakNumber = 1, breakRemain = 1;
	//最大箱の数
	int breakNumberMax = 1, breakRemainMax = 1;
	//魚の数
	int fishNumber = 1, fishRemain = 1;
};

