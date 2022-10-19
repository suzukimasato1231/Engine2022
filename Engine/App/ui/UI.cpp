#include "UI.h"
#include"../stage/Stage.h"
#include"DebugText.h"
UI::UI()
{
}
UI::~UI()
{
}
void UI::Init()
{
	boxGraph = Sprite::Get()->SpriteCreate(L"Resources/UI/UIBox.png");
	playerIcon = Sprite::Get()->SpriteCreate(L"Resources/UI/penginIcon.png");
	fishGraph = Sprite::Get()->SpriteCreate(L"Resources/UI/fish.png");

	uiNumber[0] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber1.png");
	uiNumber[1] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber2.png");
	uiNumber[2] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber3.png");
	uiNumber[3] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber4.png");
	uiNumber[4] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber5.png");
	uiNumber[5] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber6.png");
	uiNumber[6] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber7.png");
	uiNumber[7] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber8.png");
	uiNumber[8] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber9.png");
	uiNumber[9] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber10.png");
	uiSlash = Sprite::Get()->SpriteCreate(L"Resources/UI/UISlash.png");

	gameoverGraph = Sprite::Get()->SpriteCreate(L"Resources/gameover.png");
	selectGraph = Sprite::Get()->SpriteCreate(L"Resources/select.png");
}

void UI::Update()
{

}

void UI::Draw(int pLives, int fishNum, bool gameoverFlag, int gameoverNum)
{
	//プレイヤー残機
	Sprite::Get()->Draw(playerIcon, Vec2(1100.0f, 10.0f), 64.0f, 64.0f);
	Sprite::Get()->Draw(uiNumber[pLives], Vec2(1196.0f, 10.0f), 64.0f, 64.0f);
	//箱
	Sprite::Get()->Draw(boxGraph, Vec2(10.0f, 100.0f), 70.0f, 70.0f);
	//壊した箱の数
	int breaknumber = Stage::Get()->GetBlockNum() % 10, breakremain = Stage::Get()->GetBlockNum() / 10;
	if (breakremain >= 1)
	{
		Sprite::Get()->Draw(uiNumber[breakremain], Vec2(60.0f, 95.0f), 64.0f, 64.0f);
	}
	Sprite::Get()->Draw(uiNumber[breaknumber], Vec2(96.0f, 95.0f), 64.0f, 64.0f);

	Sprite::Get()->Draw(uiSlash, Vec2(128.0f, 100.0f), 64.0f, 64.0f);
	//最大箱の数
	breaknumber = Stage::Get()->GetBlockMax() % 10, breakremain = Stage::Get()->GetBlockMax() / 10;
	if (breakremain >= 1)
	{
		Sprite::Get()->Draw(uiNumber[breakremain], Vec2(160.0f, 105.0f), 64.0f, 64.0f);
	}
	Sprite::Get()->Draw(uiNumber[breaknumber], Vec2(192.0f, 105.0f), 64.0f, 64.0f);
	//魚ゲット数	
	Sprite::Get()->Draw(fishGraph, Vec2(10.0f, 10.0f), 83.0f, 54.0f);
	int boxnumber = fishNum % 10, boxremain = fishNum / 10;
	if (boxremain >= 1)
	{
		Sprite::Get()->Draw(uiNumber[boxremain], Vec2(74.0f, 0.0f), 64.0f, 64.0f);
	}
	Sprite::Get()->Draw(uiNumber[boxnumber], Vec2(106.0f, 0.0f), 64.0f, 64.0f);
	//ゲームオーバー時の描画
	if (gameoverFlag == true)
	{
		Sprite::Get()->Draw(gameoverGraph, Vec2(0.0f, 0.0f), 1280.0f, 720.0f);
		if (gameoverNum == 2)
		{
			Sprite::Get()->Draw(selectGraph, Vec2(220.0f, 400.0f), 349.0f, 143.0f);
		}
		else if (gameoverNum == 1)
		{
			Sprite::Get()->Draw(selectGraph, Vec2(744.0f, 400.0f), 349.0f, 143.0f);
		}
	}
}
