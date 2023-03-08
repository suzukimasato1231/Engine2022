#include "DecLifeStaging.h"

DecLifeStaging::DecLifeStaging()
{}

DecLifeStaging::~DecLifeStaging()
{}

void DecLifeStaging::Init()
{
	m_decGraph = Sprite::Get()->SpriteCreate(L"Resources/UI/decLife.png");
	m_gameoverGraph[0] = Sprite::Get()->SpriteCreate(L"Resources/gameover/1.png");
	m_gameoverGraph[1] = Sprite::Get()->SpriteCreate(L"Resources/gameover/2.png");
	m_gameoverGraph[2] = Sprite::Get()->SpriteCreate(L"Resources/gameover/3.png");
	m_gameoverGraph[3] = Sprite::Get()->SpriteCreate(L"Resources/gameover/4.png");
	m_gameoverGraph[4] = Sprite::Get()->SpriteCreate(L"Resources/gameover/5.png");
	m_gameoverGraph[5] = Sprite::Get()->SpriteCreate(L"Resources/gameover/6.png");
	m_gameoverGraph[6] = Sprite::Get()->SpriteCreate(L"Resources/gameover/7.png");
	m_gameoverSelect[0] = Sprite::Get()->SpriteCreate(L"Resources/gameover/select.png");
	m_gameoverSelect[1] = Sprite::Get()->SpriteCreate(L"Resources/gameover/retry.png");
	m_selectGraph = Sprite::Get()->SpriteCreate(L"Resources/select.png");
}

void DecLifeStaging::Update(const int decTime,const bool gameoverFlag)
{
	//�Ó]����
	Blackout(decTime,gameoverFlag);
	//�����̍X�V
	LetterMove();
}

void DecLifeStaging::Draw(bool gameoverFlag, int gameoverNum)
{
	Sprite::Get()->Draw(m_decGraph, Vec2(),
		static_cast<float>(window_width), static_cast<float>(window_height),
		Vec2(), m_color);
	//�Q�[���I�[�o�[���̕`��
	if (gameoverFlag == false) { return; }

	for (size_t i = 0; i < charNum; i++)
	{
		Sprite::Get()->Draw(m_gameoverGraph[i], Vec2(210.0f + 140.0f * i, 84.0f + m_charPos[i]),
			167.0f, 219.0f, Vec2(), Vec4(1.0f, 1.0f, 1.0f, 1.0f) * m_charColor[i]);
	}
	if (gameoverNum == RETRY)
	{
		Sprite::Get()->Draw(m_selectGraph, Vec2(220.0f, 400.0f), c_framSize.x, c_framSize.y);
		Sprite::Get()->Draw(m_gameoverSelect[0], Vec2(387.0f, 474.0f),
			c_selectSize.x * m_selectScale, c_selectSize.y * m_selectScale, Vec2(0.5f, 0.5f));
		Sprite::Get()->Draw(m_gameoverSelect[1], Vec2(917.0f, 474.0f),
			c_selectSize.x, c_selectSize.y, Vec2(0.5f, 0.5f));
	}
	else if (gameoverNum == SELECT)
	{
		Sprite::Get()->Draw(m_selectGraph, Vec2(744.0f, 400.0f), c_framSize.x, c_framSize.y);
		Sprite::Get()->Draw(m_gameoverSelect[0], Vec2(387.0f, 474.0f),
			c_selectSize.x, c_selectSize.y, Vec2(0.5f, 0.5f));
		Sprite::Get()->Draw(m_gameoverSelect[1], Vec2(917.0f, 474.0f),
			c_selectSize.x * m_selectScale, c_selectSize.y * m_selectScale, Vec2(0.5f, 0.5f));
	}
}

void DecLifeStaging::Reset()
{
	m_isStart = false;
	m_color = {};
}

void DecLifeStaging::Blackout(const int decTime,const bool gameoverFlag)
{
	//�Ó]�J�n
	if (decTime > 0 && m_isStart == false)
	{
		m_isStart = true;
		m_gameoverStartFlag = false;
		for (size_t i = 0; i < charNum; i++)
		{
			m_charFlag[i] = false;
			m_charColor[i] = {};
		}
	}
	//�Ó]��
	if (m_isStart == true)
	{
		m_color.w += c_blackSpeed;
		//�Q�[���I�[�o�[���͊��S�ɐ^���Âɂ��Ȃ�
		if (gameoverFlag == true && m_color.w >= c_blackColorMax)
		{
			m_color.w = c_blackColorMax;
			m_gameoverStartFlag = true;
		}
		//�^���ÂɂȂ�����Ó]�I��
		if (m_color.w >= c_colorMax)
		{
			m_isStart = false;
		}
	}
	else
	{
		if (m_color.w > 0.0f)
		{
			m_color.w -= c_blackSpeed;
		}
	}
}

void DecLifeStaging::LetterMove()
{
	//�Q�[���I�[�o�[���̉��o�̏���
	if (m_gameoverStartFlag == true)
	{
		m_gameoverTime++;
		for (size_t i = 0; i < charNum; i++)
		{
			//���ԂɂȂ����������瓧���x�𖳂���
			if (m_gameoverTime >= i * 10)
			{
				m_charFlag[i] = true;
			}
			if (m_charFlag[i] == true)
			{
				//�F�����X�ɏo��
				m_charColor[i] += c_charColorSpeed;
				if (m_charColor[i] >= c_colorMax) { m_charColor[i] = c_colorMax; }
				//�������㉺�ɗh�炷
				if (m_charPosFlag[i] == true) { m_charPos[i] -= c_charPosSpeed; }
				else { m_charPos[i] += c_charPosSpeed; }

				if (m_charPos[i] >= c_charPosMax) { m_charPosFlag[i] = true; }
				else if (m_charPos[i] <= -c_charPosMax) { m_charPosFlag[i] = false; }
			}
		}
	}
	//�Z���N�g���̋���
	if (m_selectScaleFlag == true)
	{
		m_selectScale += c_scaleSpeed;

		if (m_selectScale >= c_scaleMax)
		{
			m_selectScale = c_scaleMax;
			m_selectScaleFlag = false;
		}
	}
	else
	{
		m_selectScale -= c_scaleSpeed;
		if (m_selectScale <= c_scaleMin)
		{
			m_selectScale = c_scaleMin;
			m_selectScaleFlag = true;
		}
	}
}
