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
	gameover2Graph = Sprite::Get()->SpriteCreate(L"Resources/gameover.png");
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
	//�Ó]�J�n
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
	//�Ó]��
	if (isStart == true)
	{
		color.w += speed;
		//�Q�[���I�[�o�[���͊��S�ɐ^���Âɂ��Ȃ�
		if (gameoverFlag == true && color.w >= gameoverColor)
		{
			color.w = gameoverColor;
			gameoverStartFlag = true;
		}
		//�^���ÂɂȂ�����Ó]�I��
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

	//�Q�[���I�[�o�[���̉��o�̏���
	if (gameoverStartFlag)
	{
		gameoverTime++;
		for (size_t i = 0; i < 7; i++)
		{
			//���ԂɂȂ����������瓧���x�𖳂���
			if (gameoverTime >= i * 10)
			{
				charFlag[i] = true;
			}
			if (charFlag[i] == true)
			{
				//�F�����X�ɏo��
				charColor[i] += 0.01f;
				if (charColor[i] >= 1.0f)
				{
					charColor[i] = 1.0f;
				}
				//�������㉺�ɗh�炷
				if (charPosFlag[i] == true) { charPos[i] -= charPosSpeed; }
				else { charPos[i] += charPosSpeed; }

				if (charPos[i] >= 10.0f) { charPosFlag[i] = true; }
				else if (charPos[i] <= -10.0f) { charPosFlag[i] = false; }
			}
		}
	}
}

void DecLifeStaging::Draw(bool gameoverFlag, int gameoverNum)
{

	Sprite::Get()->Draw(decGraph, Vec2(), static_cast<float>(window_width), static_cast<float>(window_height), Vec2(), color);

	//�Q�[���I�[�o�[���̕`��
	if (gameoverFlag == true)
	{
		Sprite::Get()->Draw(gameover2Graph, Vec2(), static_cast<float>(window_width), static_cast<float>(window_height));
		for (size_t i = 0; i < 7; i++)
		{
			Sprite::Get()->Draw(gameoverGraph[i], Vec2(210.0f + 140.0f * i, 84.0f + charPos[i]), 167.0f, 219.0f, Vec2(), Vec4(1.0f, 1.0f, 1.0f, 1.0f) * charColor[i]);
		}
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

void DecLifeStaging::Reset()
{
	isStart = false;
	color = { 0.0f,0.0f,0.0f,0.0f };
}
