#include "UI.h"
#include"Stage.h"
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


}

void UI::Update()
{

}

void UI::Draw()
{
	int p = 0;
	int box = 7;

	//プレイヤー残機
	Sprite::Get()->Draw(playerIcon, Vec2(1100.0f, 10.0f), 64.0f, 64.0f);
	Sprite::Get()->Draw(uiNumber[p], Vec2(1196.0f, 10.0f), 64.0f, 64.0f);
	//箱
	Sprite::Get()->Draw(boxGraph, Vec2(10.0f, 100.0f), 70.0f, 70.0f);
	//壊した箱の数
	int breaknumber = Stage::Get()->GetBlockNum() % 10, breakremain = Stage::Get()->GetBlockNum() / 10;
	if (breakremain >= 1)
	{
		Sprite::Get()->Draw(uiNumber[breakremain], Vec2(70.0f, 95.0f), 64.0f, 64.0f);
	}
	Sprite::Get()->Draw(uiNumber[breaknumber], Vec2(106.0f, 95.0f), 64.0f, 64.0f);

	Sprite::Get()->Draw(uiSlash, Vec2(138.0f, 100.0f), 64.0f, 64.0f);
	//最大箱の数
	breaknumber = Stage::Get()->GetStageBlock() % 10, breakremain = Stage::Get()->GetStageBlock() / 10;
	if (breakremain >= 1)
	{
		Sprite::Get()->Draw(uiNumber[breakremain], Vec2(170.0f, 105.0f), 64.0f, 64.0f);
	}
	Sprite::Get()->Draw(uiNumber[breaknumber], Vec2(202.0f, 105.0f), 64.0f, 64.0f);
	//魚ゲット数	
	Sprite::Get()->Draw(fishGraph, Vec2(10.0f, 10.0f), 83.0f, 54.0f);
	int boxnumber = box % 10, boxremain = box / 10;
	if (boxremain >= 1)
	{
		Sprite::Get()->Draw(uiNumber[boxnumber], Vec2(64.0f, 0.0f), 64.0f, 64.0f);
	}
	Sprite::Get()->Draw(uiNumber[boxremain], Vec2(96.0f, 0.0f), 64.0f, 64.0f);
}
