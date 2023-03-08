#include"Menu.h"
#include<Input.h>
#include <Easing.h>
#include<Audio.h>
Menu::Menu()
{}

Menu::~Menu()
{}

void Menu::Init()
{
	m_menuButton = Sprite::Get()->SpriteCreate(L"Resources/UI/menuButton.png");
	m_menuFream = Sprite::Get()->SpriteCreate(L"Resources/UI/menuFrame.png");
	m_menuFreamFish = Sprite::Get()->SpriteCreate(L"Resources/UI/menuFrameFish.png");
	m_menuRetry = Sprite::Get()->SpriteCreate(L"Resources/UI/menuRetry.png");
	m_menuVolum = Sprite::Get()->SpriteCreate(L"Resources/UI/menuVolume.png");
	m_menuStageSelect = Sprite::Get()->SpriteCreate(L"Resources/UI/menuStageSelect.png");
	m_menuFish = Sprite::Get()->SpriteCreate(L"Resources/UI/menuFish.png");

	m_menuAudioFream = Sprite::Get()->SpriteCreate(L"Resources/UI/menuAudioFrame.png");
	m_menuAudioVolum = Sprite::Get()->SpriteCreate(L"Resources/UI/menuAudioVolum.png");
	m_menuAudioLandmark = Sprite::Get()->SpriteCreate(L"Resources/UI/menuAudioLandmark.png");

	m_decisionSE = Audio::SoundLoadWave("Resources/sound/SE/menu.wav");
	m_selectSE = Audio::SoundLoadWave("Resources/sound/SE/menuSelect.wav");
}

void Menu::Update(bool& menuFlag, bool& changeScene, int& sceneNum)
{
	//メニュー画面
	if (Input::Get()->ControllerDown(ButtonMenu) == true && menuFlag == false)
	{
		menuFlag = true;
		m_menuNum = 0;
		m_startTime = 0.0f;
		m_menuEasingFlag = true;
		Audio::Get()->SoundSEPlayWave(m_decisionSE);
	}


	if (menuFlag == true && m_audioFlag == false)
	{
		if (Input::Get()->ControllerDown(ButtonB) == true)
		{
			menuFlag = false;
			m_startTime = 0;
			Audio::Get()->SoundSEPlayWave(m_decisionSE);
		}
		if (Input::Get()->ControllerDown(ButtonA) == true)
		{
			switch (m_menuNum)
			{
			case MENURETRY://リトライ
				sceneNum = 1;
				changeScene = true;
				break;
			case MENUVOLUM://音量調整
				m_audioFlag = true;
				break;
			case MENUSTAGESELECT://ステージセレクト
				sceneNum = 2;
				changeScene = true;
				break;
			default:
				assert(0);
				break;
			}
			Audio::Get()->SoundSEPlayWave(m_decisionSE);
		}
		if (Input::Get()->ControllerDown(LButtonDown) == true)
		{
			m_menuNum++;
			if (m_menuNum >= MENUMAX)
			{
				m_menuNum = MENURETRY;
			}
			Audio::Get()->SoundSEPlayWave(m_selectSE);
		}
		if (Input::Get()->ControllerDown(LButtonUp) == true)
		{
			m_menuNum--;
			if (m_menuNum < MENURETRY)
			{
				m_menuNum = MENUSTAGESELECT;
			}
			Audio::Get()->SoundSEPlayWave(m_selectSE);
		}
	}

	if (m_audioFlag == true)
	{
		if (Input::Get()->ControllerPush(LButtonLeft) == true)
		{
			m_volum -= 0.001f;
			if (m_volum <= c_volumMin)
			{
				m_volum = c_volumMin;
			}
			Audio::Get()->SoundSEPlayWave(m_selectSE);
		}
		if (Input::Get()->ControllerPush(LButtonRight) == true)
		{
			m_volum += 0.001f;
			if (m_volum >= c_volumMax)
			{
				m_volum = c_volumMax;
			}
			Audio::Get()->SoundSEPlayWave(m_selectSE);
		}
		Audio::Get()->SetVolume(m_volum);
		if (Input::Get()->ControllerDown(ButtonB) == true)
		{
			m_audioFlag = false;
			Audio::Get()->SoundSEPlayWave(m_decisionSE);
		}
	}


	//メニュー選択してるのを目立たせる処理
	if (m_menuScale >= 1.1f)
	{
		m_menuTimeFlag = true;
	}
	if (m_menuScale <= 0.9f)
	{
		m_menuTimeFlag = false;
	}
	if (m_menuTimeFlag == false)
	{
		m_menuScale += 0.01f;
	}
	else
	{
		m_menuScale -= 0.01f;
	}
	//イージング処理
	if (m_menuEasingFlag == true)
	{
		if (menuFlag == true)
		{
			float t = min(m_startTime / c_startTimeMax, 1.0f);
			if (t <= 1.0f)
			{
				m_startTime += 1.0f;
			}
			m_menuPos = Easing::easeOut(c_start, c_end, t);
		}
		else
		{
			float t = min(m_startTime / c_startTimeMax, 1.0f);
			m_startTime += 1.0f;
			if (t >= 1.0f)
			{
				m_menuEasingFlag = false;
			}
			m_menuPos = Easing::easeIn(c_end, c_start, t);
		}
	}
}

void Menu::Draw(const bool gameoverFlag)
{
	//メニュー
	Sprite::Get()->Draw(m_menuButton, Vec2(1230.5f, 110.0f), 96.0f, 32.0f, Vec2(0.5f, 0.5f));
	
	if (m_menuEasingFlag == true && gameoverFlag == false && m_audioFlag == false)
	{
		Sprite::Get()->Draw(m_menuFream, Vec2(m_menuPos.x + 26.5f, 300.5), 459.0, 547.0f, Vec2(0.5f, 0.5f));
		Sprite::Get()->Draw(m_menuFreamFish, Vec2(m_menuPos.x , 300.5), 512.0f, 549.0f, Vec2(0.5f, 0.5f));
		float UIPosX = 30.0f + m_menuPos.x;
		if (m_menuNum == MENURETRY)
		{
			Sprite::Get()->Draw(m_menuRetry, Vec2(UIPosX, 150.5f), 359.0f * m_menuScale, 71.0f * m_menuScale, Vec2(0.5f, 0.5f));
		}
		else
		{
			Sprite::Get()->Draw(m_menuRetry, Vec2(UIPosX, 150.5f), 359.0f, 71.0f, Vec2(0.5f, 0.5f));
		}
		if (m_menuNum == MENUVOLUM)
		{
			Sprite::Get()->Draw(m_menuVolum, Vec2(UIPosX, 280.5f), 359.0f * m_menuScale, 71.0f * m_menuScale, Vec2(0.5f, 0.5f));
		}
		else
		{
			Sprite::Get()->Draw(m_menuVolum, Vec2(UIPosX, 280.5f), 359.0f, 71.0f, Vec2(0.5f, 0.5f));
		}
		if (m_menuNum == MENUSTAGESELECT)
		{
			Sprite::Get()->Draw(m_menuStageSelect, Vec2(UIPosX, 400.5f), 359.0f * m_menuScale, 71.0f * m_menuScale, Vec2(0.5f, 0.5f));
		}
		else
		{
			Sprite::Get()->Draw(m_menuStageSelect, Vec2(UIPosX, 400.5f), 359.0f, 71.0f, Vec2(0.5f, 0.5f));
		}
	}
	if (m_audioFlag == true)
	{
		Sprite::Get()->Draw(m_menuFream, Vec2(m_menuPos.x + 26.5f, 300.5f), 459.0f, 549.0f, Vec2(0.5f, 0.5f));
		Sprite::Get()->Draw(m_menuFreamFish, Vec2(m_menuPos.x, 300.5f), 512.0f, 549.0f, Vec2(0.5f, 0.5f));
		Sprite::Get()->Draw(m_menuAudioFream, Vec2(m_menuPos.x, 300.5f), 512.0, 547.0f, Vec2(0.5f, 0.5f));
		Sprite::Get()->Draw(m_menuAudioVolum, Vec2(m_menuPos.x - 133.0f, 285.0f), 372.0f * m_volum * 10, 28.0f, Vec2(0.0f, 0.0f));
		Sprite::Get()->Draw(m_menuAudioLandmark, Vec2(m_menuPos.x - 133.0f + 372.0f * m_volum * 10, 295.0f), 12.0f, 68.0f, Vec2(0.5f, 0.5f));
	}
}

void Menu::Reset()
{
	m_menuNum = 0;
	m_startTime = 0.0f;
	m_audioFlag = false;
	m_menuEasingFlag = false;
}
