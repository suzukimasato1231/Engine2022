#include "DecLifeStaging.h"

DecLifeStaging::DecLifeStaging()
{
}

DecLifeStaging::~DecLifeStaging()
{
}

void DecLifeStaging::Init()
{
	decGraph = Sprite::Get()->SpriteCreate(L"Resources/UI/decLife.png");
	gameoverGraph[0] = Sprite::Get()->SpriteCreate(L"Resources/gameover/1.png");
	gameoverGraph[1] = Sprite::Get()->SpriteCreate(L"Resources/gameover/2.png");
	gameoverGraph[2] = Sprite::Get()->SpriteCreate(L"Resources/gameover/3.png");
	gameoverGraph[3] = Sprite::Get()->SpriteCreate(L"Resources/gameover/4.png");
	gameoverGraph[4] = Sprite::Get()->SpriteCreate(L"Resources/gameover/5.png");
	gameoverGraph[5] = Sprite::Get()->SpriteCreate(L"Resources/gameover/6.png");
	gameoverGraph[6] = Sprite::Get()->SpriteCreate(L"Resources/gameover/7.png");
	gameoverSelect[0] = Sprite::Get()->SpriteCreate(L"Resources/gameover/select.png");
	gameoverSelect[1] = Sprite::Get()->SpriteCreate(L"Resources/gameover/retry.png");
	selectGraph = Sprite::Get()->SpriteCreate(L"Resources/select.png");
}

void DecLifeStaging::Update(int decTime, bool gameoverFlag)
{
	//暗転開始
	if (decTime > 0 && isStart == false)
	{
		isStart = true;
		gameoverStartFlag = false;
		for (size_t i = 0; i < 7; i++)
		{
			charFlag[i] = false;
			charColor[i] = 0.0f;
		}
	}
	//暗転中
	if (isStart == true)
	{
		color.w += speed;
		//ゲームオーバー中は完全に真っ暗にしない
		if (gameoverFlag == true && color.w >= gameoverColor)
		{
			color.w = gameoverColor;
			gameoverStartFlag = true;
		}
		//真っ暗になったら暗転終了
		if (color.w >= 1.0f)
		{
			isStart = false;
		}
	}
	else
	{
		if (color.w > 0.0f)
		{
			color.w -= speed;
		}
	}

	//ゲームオーバー時の演出の処理
	if (gameoverStartFlag==true)
	{
		gameoverTime++;
		for (size_t i = 0; i < 7; i++)
		{
			//時間になった文字から透明度を無くす
			if (gameoverTime >= i * 10)
			{
				charFlag[i] = true;
			}
			if (charFlag[i] == true)
			{
				//色を徐々に出す
				charColor[i] += 0.01f;
				if (charColor[i] >= 1.0f){charColor[i] = 1.0f;}
				//文字を上下に揺らす
				if (charPosFlag[i] == true) { charPos[i] -= charPosSpeed; }
				else { charPos[i] += charPosSpeed; }

				if (charPos[i] >= 10.0f) { charPosFlag[i] = true; }
				else if (charPos[i] <= -10.0f) { charPosFlag[i] = false; }
			}
		}
	}
	//セレクト時の強調
	if (selectScaleFlag == true)
	{
		selectScale += speed;

		if (selectScale >= 1.3f)
		{
			selectScale = 1.3f;
			selectScaleFlag = false;
		}
	}
	else
	{
		selectScale -= speed;
		if (selectScale <= 1.0f)
		{
			selectScale = 1.0f;
			selectScaleFlag = true;
		}
	}

}

void DecLifeStaging::Draw(bool gameoverFlag, int gameoverNum)
{

	Sprite::Get()->Draw(decGraph, Vec2(), static_cast<float>(window_width), static_cast<float>(window_height), Vec2(), color);

	//ゲームオーバー時の描画
	if (gameoverFlag == true)
	{
		for (size_t i = 0; i < 7; i++)
		{
			Sprite::Get()->Draw(gameoverGraph[i], Vec2(210.0f + 140.0f * i, 84.0f + charPos[i]), 167.0f, 219.0f, Vec2(), Vec4(1.0f, 1.0f, 1.0f, 1.0f) * charColor[i]);
		}
		if (gameoverNum == 2)
		{
			Sprite::Get()->Draw(selectGraph, Vec2(220.0f, 400.0f), 349.0f, 143.0f);
			Sprite::Get()->Draw(gameoverSelect[0], Vec2(387.0f, 474.0f), 334.0f * selectScale, 128.0f * selectScale, Vec2(0.5f, 0.5f));
			Sprite::Get()->Draw(gameoverSelect[1], Vec2(917.0f, 474.0f), 334.0f, 128.0f, Vec2(0.5f, 0.5f));
		}
		else if (gameoverNum == 1)
		{
			Sprite::Get()->Draw(selectGraph, Vec2(744.0f, 400.0f), 349.0f, 143.0f);
			Sprite::Get()->Draw(gameoverSelect[0], Vec2(387.0f, 474.0f), 334.0f, 128.0f, Vec2(0.5f, 0.5f));
			Sprite::Get()->Draw(gameoverSelect[1], Vec2(917.0f, 474.0f), 334.0f * selectScale, 128.0f * selectScale, Vec2(0.5f, 0.5f));
		}

	}
}

void DecLifeStaging::Reset()
{
	isStart = false;
	color = { 0.0f,0.0f,0.0f,0.0f };
}
