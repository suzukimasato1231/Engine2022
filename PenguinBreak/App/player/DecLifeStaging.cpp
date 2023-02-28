#include "DecLifeStaging.h"

DecLifeStaging::DecLifeStaging()
{}

DecLifeStaging::~DecLifeStaging()
{}

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

void DecLifeStaging::Update(const int decTime,const bool gameoverFlag)
{
	//暗転処理
	Blackout(decTime,gameoverFlag);
	//文字の更新
	LetterMove();
}

void DecLifeStaging::Draw(bool gameoverFlag, int gameoverNum)
{
	Sprite::Get()->Draw(decGraph, Vec2(),
		static_cast<float>(window_width), static_cast<float>(window_height),
		Vec2(), color);
	//ゲームオーバー時の描画
	if (gameoverFlag == false) { return; }

	for (size_t i = 0; i < charNum; i++)
	{
		Sprite::Get()->Draw(gameoverGraph[i], Vec2(210.0f + 140.0f * i, 84.0f + charPos[i]),
			167.0f, 219.0f, Vec2(), Vec4(1.0f, 1.0f, 1.0f, 1.0f) * charColor[i]);
	}
	if (gameoverNum == RETRY)
	{
		Sprite::Get()->Draw(selectGraph, Vec2(220.0f, 400.0f), framSize.x, framSize.y);
		Sprite::Get()->Draw(gameoverSelect[0], Vec2(387.0f, 474.0f),
			selectSize.x * selectScale, selectSize.y * selectScale, Vec2(0.5f, 0.5f));
		Sprite::Get()->Draw(gameoverSelect[1], Vec2(917.0f, 474.0f),
			selectSize.x, selectSize.y, Vec2(0.5f, 0.5f));
	}
	else if (gameoverNum == SELECT)
	{
		Sprite::Get()->Draw(selectGraph, Vec2(744.0f, 400.0f), framSize.x, framSize.y);
		Sprite::Get()->Draw(gameoverSelect[0], Vec2(387.0f, 474.0f),
			selectSize.x, selectSize.y, Vec2(0.5f, 0.5f));
		Sprite::Get()->Draw(gameoverSelect[1], Vec2(917.0f, 474.0f),
			selectSize.x * selectScale, selectSize.y * selectScale, Vec2(0.5f, 0.5f));
	}
}

void DecLifeStaging::Reset()
{
	isStart = false;
	color = {};
}

void DecLifeStaging::Blackout(const int decTime,const bool gameoverFlag)
{
	//暗転開始
	if (decTime > 0 && isStart == false)
	{
		isStart = true;
		gameoverStartFlag = false;
		for (size_t i = 0; i < charNum; i++)
		{
			charFlag[i] = false;
			charColor[i] = {};
		}
	}
	//暗転中
	if (isStart == true)
	{
		color.w += blackSpeed;
		//ゲームオーバー中は完全に真っ暗にしない
		if (gameoverFlag == true && color.w >= blackColorMax)
		{
			color.w = blackColorMax;
			gameoverStartFlag = true;
		}
		//真っ暗になったら暗転終了
		if (color.w >= colorMax)
		{
			isStart = false;
		}
	}
	else
	{
		if (color.w > 0.0f)
		{
			color.w -= blackSpeed;
		}
	}
}

void DecLifeStaging::LetterMove()
{
	//ゲームオーバー時の演出の処理
	if (gameoverStartFlag == true)
	{
		gameoverTime++;
		for (size_t i = 0; i < charNum; i++)
		{
			//時間になった文字から透明度を無くす
			if (gameoverTime >= i * 10)
			{
				charFlag[i] = true;
			}
			if (charFlag[i] == true)
			{
				//色を徐々に出す
				charColor[i] += charColorSpeed;
				if (charColor[i] >= colorMax) { charColor[i] = colorMax; }
				//文字を上下に揺らす
				if (charPosFlag[i] == true) { charPos[i] -= charPosSpeed; }
				else { charPos[i] += charPosSpeed; }

				if (charPos[i] >= charPosMax) { charPosFlag[i] = true; }
				else if (charPos[i] <= -charPosMax) { charPosFlag[i] = false; }
			}
		}
	}
	//セレクト時の強調
	if (selectScaleFlag == true)
	{
		selectScale += scaleSpeed;

		if (selectScale >= scaleMax)
		{
			selectScale = scaleMax;
			selectScaleFlag = false;
		}
	}
	else
	{
		selectScale -= scaleSpeed;
		if (selectScale <= scaleMin)
		{
			selectScale = scaleMin;
			selectScaleFlag = true;
		}
	}
}
