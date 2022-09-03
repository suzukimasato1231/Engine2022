#pragma once
#include"Singleton.h"
#include"Sprite.h"
class UI :public Singleton<UI>
{
private:
	friend Singleton<UI>;
public:
	UI();
	~UI();

	void Init();

	void Update();

	void Draw(int pLives, int fishNum, bool gameoverFlag, int gameoverNum = 0);

private:
	SpriteData boxGraph;

	SpriteData playerIcon;

	SpriteData fishGraph;

	SpriteData uiNumber[10];
	SpriteData uiSlash;
	//ゲームオーバー時の
	SpriteData gameoverGraph;
	SpriteData selectGraph;
};

