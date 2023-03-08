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
	m_boxGraph = Sprite::Get()->SpriteCreate(L"Resources/UI/UIBox.png");
	m_playerIcon = Sprite::Get()->SpriteCreate(L"Resources/UI/penginIcon.png");
	m_fishGraph = Sprite::Get()->SpriteCreate(L"Resources/UI/fish.png");

	m_uiNumber[0] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber1.png");
	m_uiNumber[1] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber2.png");
	m_uiNumber[2] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber3.png");
	m_uiNumber[3] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber4.png");
	m_uiNumber[4] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber5.png");
	m_uiNumber[5] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber6.png");
	m_uiNumber[6] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber7.png");
	m_uiNumber[7] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber8.png");
	m_uiNumber[8] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber9.png");
	m_uiNumber[9] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber10.png");
	m_uiSlash = Sprite::Get()->SpriteCreate(L"Resources/UI/UISlash.png");

	m_menu.Init();
}

void UI::Update(int fishNum, bool clearFlag, bool& changeScene, int& sceneNum)
{
	//壊した箱の数	
	int breaknumber = Stage::Get()->GetBlockNum() % 10;
	if (m_breakNumber != breaknumber)
	{
		m_breakNumber = breaknumber;
		m_stagingTime[0] = c_stagingTimeMax;
		m_stagingFlag[0] = true;
	}
	int breakremain = Stage::Get()->GetBlockNum() / 10;
	if (m_breakRemain != breakremain)
	{
		m_breakRemain = breakremain;
		m_stagingTime[1] = c_stagingTimeMax;
		m_stagingFlag[1] = true;
	}
	//最大箱の数
	m_breakNumberMax = Stage::Get()->GetBlockMax() % 10;
	m_breakRemainMax = Stage::Get()->GetBlockMax() / 10;
	//魚数
	int fishnumber = fishNum % 10;
	if (m_fishNumber != fishnumber)
	{
		m_fishNumber = fishnumber;
		m_stagingTime[2] = c_stagingTimeMax;
		m_stagingFlag[2] = true;
	}
	int fishremain = fishNum / 10;
	if (m_fishRemain != fishremain)
	{
		m_fishRemain = fishremain;
		m_stagingTime[3] = c_stagingTimeMax;
		m_stagingFlag[3] = true;
	}
	//数字強調処理
	for (size_t i = 0; i < 4; i++)
	{
		if (m_stagingFlag[i] == true)
		{
			m_stagingTime[i]--;
			if (c_stagingTimeMax / 2 < m_stagingTime[i])
			{
				m_stagingScale[i] += 0.1f;
				if (m_stagingScale[i] >= c_stagingScaleMax)
				{
					m_stagingScale[i] = c_stagingScaleMax;
				}
			}
			else
			{
				m_stagingScale[i] -= 0.1f;
				if (m_stagingScale[i] <= 1.0f)
				{
					m_stagingScale[i] = 1.0f;
				}
			}
			if (m_stagingTime <= 0)
			{
				m_stagingFlag[i] = false;
				m_stagingScale[i] = 1.0f;
			}
		}
	}

	if (clearFlag == false)
	{
		m_menu.Update(m_menuFlag, changeScene, sceneNum);
	}
}


void UI::Draw(const int pLives, const  bool gameoverFlag)
{
	//プレイヤー残機
	Sprite::Get()->Draw(m_playerIcon, Vec2(1132.0f, 42.0f), 64.0f, 64.0f, Vec2(0.5f, 0.5f));
	Sprite::Get()->Draw(m_uiNumber[pLives], Vec2(1228.0f, 42.0f), 64.0f, 64.0f, Vec2(0.5f, 0.5f));
	//箱
	Sprite::Get()->Draw(m_boxGraph, Vec2(45.0f, 135.0f), 70.0f, 70.0f, Vec2(0.5f, 0.5f));

	if (m_breakRemain >= 1)
	{
		Sprite::Get()->Draw(m_uiNumber[m_breakRemain], Vec2(92.0f, 127.0f), 64.0f * m_stagingScale[1], 64.0f * m_stagingScale[1], Vec2(0.5f, 0.5f));
	}
	Sprite::Get()->Draw(m_uiNumber[m_breakNumber], Vec2(128.0f, 127.0f), 64.0f * m_stagingScale[0], 64.0f * m_stagingScale[0], Vec2(0.5f, 0.5f));

	Sprite::Get()->Draw(m_uiSlash, Vec2(160.0f, 132.0f), 64.0f, 64.0f, Vec2(0.5f, 0.5f));

	if (m_breakRemainMax >= 1)
	{
		Sprite::Get()->Draw(m_uiNumber[m_breakRemainMax], Vec2(192.0f, 137.0f), 64.0f, 64.0f, Vec2(0.5f, 0.5f));
	}
	Sprite::Get()->Draw(m_uiNumber[m_breakNumberMax], Vec2(224.0f, 137.0f), 64.0f, 64.0f, Vec2(0.5f, 0.5f));
	//魚ゲット数	
	Sprite::Get()->Draw(m_fishGraph, Vec2(51.5f, 37.0f), 83.0f, 54.0f, Vec2(0.5f, 0.5f));
	if (m_fishRemain >= 1)
	{
		Sprite::Get()->Draw(m_uiNumber[m_fishRemain], Vec2(108.0f, 32.0f), 64.0f * m_stagingScale[3], 64.0f * m_stagingScale[3], Vec2(0.5f, 0.5f));
	}
	Sprite::Get()->Draw(m_uiNumber[m_fishNumber], Vec2(138.0f, 32.0f), 64.0f * m_stagingScale[2], 64.0f * m_stagingScale[2], Vec2(0.5f, 0.5f));

	m_menu.Draw(gameoverFlag);
}

void UI::Reset()
{
	m_menuFlag = false;
	m_menu.Reset();

}
