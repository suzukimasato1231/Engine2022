#include"Menu.h"
#include<Input.h>
#include <Easing.h>
#include<Audio.h>
Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::Init()
{
	menuButton = Sprite::Get()->SpriteCreate(L"Resources/UI/menuButton.png");
	menuFream = Sprite::Get()->SpriteCreate(L"Resources/UI/menuFrame.png");
	menuRetry = Sprite::Get()->SpriteCreate(L"Resources/UI/menuRetry.png");
	menuVolum = Sprite::Get()->SpriteCreate(L"Resources/UI/menuVolume.png");
	menuStageSelect = Sprite::Get()->SpriteCreate(L"Resources/UI/menuStageSelect.png");
	menuFish = Sprite::Get()->SpriteCreate(L"Resources/UI/menuFish.png");

	menuAudioFream = Sprite::Get()->SpriteCreate(L"Resources/UI/menuAudioFrame.png");
	menuAudioVolum = Sprite::Get()->SpriteCreate(L"Resources/UI/menuAudioVolum.png");;
	menuAudioLandmark = Sprite::Get()->SpriteCreate(L"Resources/UI/menuAudioLandmark.png");;
}

void Menu::Update(bool& menuFlag, bool& changeScene, int& sceneNum)
{
	//メニュー画面
	if (Input::Get()->ControllerDown(ButtonMenu) == true && menuFlag == false)
	{
		menuFlag = true;
		menuNum = 0;
		m_startTime = 0.0f;
		menuEasingFlag = true;
	}


	if (menuFlag == true && audioFlag == false)
	{
		if (Input::Get()->ControllerDown(ButtonB) == true)
		{
			menuFlag = false;
			m_startTime = 0;
		}
		if (Input::Get()->ControllerDown(ButtonA) == true)
		{
			switch (menuNum)
			{
			case 0://リトライ
				sceneNum = 1;
				changeScene = true;
				break;
			case 1://音量調整
				audioFlag = true;
				break;
			case 2://ステージセレクト
				sceneNum = 2;
				changeScene = true;
				break;
			default:
				assert(0);
				break;
			}
		}
		if (Input::Get()->ControllerDown(LButtonDown) == true)
		{
			menuNum++;
			if (menuNum >= 3)
			{
				menuNum = 0;
			}
		}
		if (Input::Get()->ControllerDown(LButtonUp) == true)
		{
			menuNum--;
			if (menuNum < 0)
			{
				menuNum = 2;
			}
		}
	}

	if (audioFlag == true)
	{
		if (Input::Get()->ControllerPush(LButtonLeft) == true)
		{
			volum -= 0.001f;
			if (volum <= volumMin)
			{
				volum = volumMin;
			}
		}
		if (Input::Get()->ControllerPush(LButtonRight) == true)
		{
			volum += 0.001f;
			if (volum >= volumMax)
			{
				volum = volumMax;
			}
		}
		Audio::Get()->SetVolume(volum);
		if (Input::Get()->ControllerDown(ButtonB) == true)
		{
			audioFlag = false;
		}
	}


	//メニュー選択してるのを目立たせる処理
	if (menuScale >= 1.1f)
	{
		menuTimeFlag = true;
	}
	if (menuScale <= 0.9f)
	{
		menuTimeFlag = false;
	}
	if (menuTimeFlag == false)
	{
		menuScale += 0.01f;
	}
	else
	{
		menuScale -= 0.01f;
	}
	//イージング処理
	if (menuEasingFlag == true)
	{
		if (menuFlag == true)
		{
			float t = min(m_startTime / c_startTimeMax, 1.0f);
			if (t <= 1.0f)
			{
				m_startTime += 1.0f;
			}
			menuPos = Easing::easeOut(c_start, c_end, t);
		}
		else
		{
			float t = min(m_startTime / c_startTimeMax, 1.0f);
			m_startTime += 1.0f;
			if (t >= 1.0f)
			{
				menuEasingFlag = false;
			}
			menuPos = Easing::easeIn(c_end, c_start, t);
		}
	}
}

void Menu::Draw(const bool gameoverFlag)
{
	//メニュー
	Sprite::Get()->Draw(menuButton, Vec2(1230.5f, 110.0f), 96.0f, 32.0f, Vec2(0.5f, 0.5f));

	if (menuEasingFlag == true && gameoverFlag == false && audioFlag == false)
	{

		Sprite::Get()->Draw(menuFream, Vec2(menuPos.x, 300.5), 512.0, 547.0f, Vec2(0.5f, 0.5f));

		float UIPosX = 50.0f + menuPos.x;
		if (menuNum == 0)
		{
			Sprite::Get()->Draw(menuRetry, Vec2(UIPosX, 150.5f), 359.0f * menuScale, 71.0f * menuScale, Vec2(0.5f, 0.5f));
		}
		else
		{
			Sprite::Get()->Draw(menuRetry, Vec2(UIPosX, 150.5f), 359.0f, 71.0f, Vec2(0.5f, 0.5f));
		}
		if (menuNum == 1)
		{
			Sprite::Get()->Draw(menuVolum, Vec2(UIPosX, 280.5f), 359.0f * menuScale, 71.0f * menuScale, Vec2(0.5f, 0.5f));
		}
		else
		{
			Sprite::Get()->Draw(menuVolum, Vec2(UIPosX, 280.5f), 359.0f, 71.0f, Vec2(0.5f, 0.5f));
		}
		if (menuNum == 2)
		{
			Sprite::Get()->Draw(menuStageSelect, Vec2(UIPosX, 400.5f), 359.0f * menuScale, 71.0f * menuScale, Vec2(0.5f, 0.5f));
		}
		else
		{
			Sprite::Get()->Draw(menuStageSelect, Vec2(UIPosX, 400.5f), 359.0f, 71.0f, Vec2(0.5f, 0.5f));
		}
		Sprite::Get()->Draw(menuFish, Vec2(-180 + menuPos.x, 140.5f + 130.0f * static_cast<float>(menuNum)), 63.0f, 54.0f, Vec2(0.5f, 0.5f));
	}
	if (audioFlag == true)
	{
		Sprite::Get()->Draw(menuFream, Vec2(menuPos.x, 300.5), 512.0, 547.0f, Vec2(0.5f, 0.5f));
		Sprite::Get()->Draw(menuAudioFream, Vec2(menuPos.x, 300.5), 512.0, 547.0f, Vec2(0.5f, 0.5f));
		Sprite::Get()->Draw(menuAudioVolum, Vec2(menuPos.x - 133.0f, 285.0f), 372.0f * volum * 10, 28.0f, Vec2(0.0f, 0.0f));
		Sprite::Get()->Draw(menuAudioLandmark, Vec2(menuPos.x - 133.0f + 372.0f * volum * 10, 295.0f), 12.0f, 68.0f, Vec2(0.5f, 0.5f));
	}
}

void Menu::Reset()
{
	menuNum = 0;
	m_startTime = 0.0f;
	audioFlag = false;
	menuEasingFlag = false;
}
