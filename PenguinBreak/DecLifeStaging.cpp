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
}

void DecLifeStaging::Update(int decTime)
{
	if (decTime > 0 && isStart == false)
	{
		isStart = true;
	}

	if (isStart == true)
	{
		color.w += speed;
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
}

void DecLifeStaging::Draw(bool gameoverFlag)
{
	if (gameoverFlag == false)
	{
		Sprite::Get()->Draw(decGraph, Vec2(), static_cast<float>(window_width), static_cast<float>(window_height), Vec2(), color);
	}
}

void DecLifeStaging::Reset()
{
	isStart = false;
	color = { 0.0f,0.0f,0.0f,0.0f };
}
