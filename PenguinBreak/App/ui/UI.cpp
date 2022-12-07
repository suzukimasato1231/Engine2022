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

	menu.Init();
}

void UI::Update(int fishNum, bool& changeScene, int& sceneNum)
{
	//壊した箱の数	
	int breaknumber = Stage::Get()->GetBlockNum() % 10;
	if (breakNumber != breaknumber)
	{
		breakNumber = breaknumber;
		stagingTime[0] = stagingTimeMax;
		stagingFlag[0] = true;
	}
	int breakremain = Stage::Get()->GetBlockNum() / 10;
	if (breakRemain != breakremain)
	{
		breakRemain = breakremain;
		stagingTime[1] = stagingTimeMax;
		stagingFlag[1] = true;
	}
	//最大箱の数
	breakNumberMax = Stage::Get()->GetBlockMax() % 10;
	breakRemainMax = Stage::Get()->GetBlockMax() / 10;
	//魚数
	int fishnumber = fishNum % 10;
	if (fishNumber != fishnumber)
	{
		fishNumber = fishnumber;
		stagingTime[2] = stagingTimeMax;
		stagingFlag[2] = true;
	}
	int fishremain = fishNum / 10;
	if (fishRemain != fishremain)
	{
		fishRemain = fishremain;
		stagingTime[3] = stagingTimeMax;
		stagingFlag[3] = true;
	}
	//数字強調処理
	for (size_t i = 0; i < 4; i++)
	{
		if (stagingFlag[i] == true)
		{
			stagingTime[i]--;
			if (stagingTimeMax / 2 < stagingTime[i])
			{
				stagingScale[i] += 0.1f;
				if (stagingScale[i] >= stagingScaleMax)
				{
					stagingScale[i] = stagingScaleMax;
				}
			}
			else
			{
				stagingScale[i] -= 0.1f;
				if (stagingScale[i] <= 1.0f)
				{
					stagingScale[i] = 1.0f;
				}
			}
			if (stagingTime <= 0)
			{
				stagingFlag[i] = false;
				stagingScale[i] = 1.0f;
			}
		}
	}


	menu.Update(menuFlag, changeScene, sceneNum);

}


void UI::Draw(const int pLives,const  bool gameoverFlag)
{
	//プレイヤー残機
	Sprite::Get()->Draw(playerIcon, Vec2(1132.0f, 42.0f), 64.0f, 64.0f, Vec2(0.5f, 0.5f));
	Sprite::Get()->Draw(uiNumber[pLives], Vec2(1228.0f, 42.0f), 64.0f, 64.0f, Vec2(0.5f, 0.5f));
	//箱
	Sprite::Get()->Draw(boxGraph, Vec2(45.0f, 135.0f), 70.0f, 70.0f, Vec2(0.5f, 0.5f));

	if (breakRemain >= 1)
	{
		Sprite::Get()->Draw(uiNumber[breakRemain], Vec2(92.0f, 127.0f), 64.0f * stagingScale[1], 64.0f * stagingScale[1], Vec2(0.5f, 0.5f));
	}
	Sprite::Get()->Draw(uiNumber[breakNumber], Vec2(128.0f, 127.0f), 64.0f * stagingScale[0], 64.0f * stagingScale[0], Vec2(0.5f, 0.5f));

	Sprite::Get()->Draw(uiSlash, Vec2(160.0f, 132.0f), 64.0f, 64.0f, Vec2(0.5f, 0.5f));

	if (breakRemainMax >= 1)
	{
		Sprite::Get()->Draw(uiNumber[breakRemainMax], Vec2(192.0f, 137.0f), 64.0f, 64.0f, Vec2(0.5f, 0.5f));
	}
	Sprite::Get()->Draw(uiNumber[breakNumberMax], Vec2(224.0f, 137.0f), 64.0f, 64.0f, Vec2(0.5f, 0.5f));
	//魚ゲット数	
	Sprite::Get()->Draw(fishGraph, Vec2(51.5f, 37.0f), 83.0f, 54.0f, Vec2(0.5f, 0.5f));
	if (fishRemain >= 1)
	{
		Sprite::Get()->Draw(uiNumber[fishRemain], Vec2(108.0f, 32.0f), 64.0f * stagingScale[3], 64.0f * stagingScale[3], Vec2(0.5f, 0.5f));
	}
	Sprite::Get()->Draw(uiNumber[fishNumber], Vec2(138.0f, 32.0f), 64.0f * stagingScale[2], 64.0f * stagingScale[2], Vec2(0.5f, 0.5f));

	menu.Draw(gameoverFlag);
}

void UI::Reset()
{
	menuFlag = false;
	menu.Reset();
	
}
