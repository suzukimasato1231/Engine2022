#include "ResultScene.h"
#include"DebugText.h"
#include"../App/stage/Stage.h"
void ResultScene::Initialize()
{
	boxGraph = Sprite::Get()->SpriteCreate(L"Resources/UI/UIBox.png");

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

	buttonGraph = Sprite::Get()->SpriteCreate(L"Resources/titleButton.png");
}
void ResultScene::Init()
{
	resultTime = 0;
}

void ResultScene::Update()
{
	//順番にリザルトが出るように
	if (resultTime <= 500)
	{
		resultTime++;
	}
	//ボタンの点滅
	buttonTime++;
	if (buttonTime >= 60)
	{
		buttonTime = 0;
	}
}

void ResultScene::Draw()
{
	if (resultTime >= 30)
	{
		//箱
		Sprite::Get()->Draw(boxGraph, Vec2(300.0f, 200.0f), 150.0f, 150.0f);
		//壊した箱の数
		int breaknumber = Stage::Get()->GetBlockNum() % 10, breakremain = Stage::Get()->GetBlockNum() / 10;
		if (breakremain >= 1)
		{
			Sprite::Get()->Draw(uiNumber[breakremain], Vec2(450.0f, 200.0f), 128.0f, 128.0f);
		}
		Sprite::Get()->Draw(uiNumber[breaknumber], Vec2(550.0f, 200.0f), 128.0f, 128.0f);

		Sprite::Get()->Draw(uiSlash, Vec2(650.0f, 200.0f), 128.0f, 128.0f);
		//最大箱の数
		breaknumber = Stage::Get()->GetBlockMax() % 10, breakremain = Stage::Get()->GetBlockMax() / 10;
		if (breakremain >= 1)
		{
			Sprite::Get()->Draw(uiNumber[breakremain], Vec2(750.0f, 200.0f), 128.0f, 128.0f);
		}
		Sprite::Get()->Draw(uiNumber[breaknumber], Vec2(850.0f, 200.0f), 128.0f, 128.0f);
	}
	if (resultTime >= 60 && buttonTime >= 30)
	{
		Sprite::Get()->Draw(buttonGraph, Vec2(420.0f, 532.0f), 512.0f, 64.0f);
	}
}
