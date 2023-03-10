#include "StageSelect.h"
#include<sstream>
#include<iomanip>
#include "Input.h"
#include"Shape.h"
#include"DebugText.h"
#include"../App/player/Player.h"
#include"Object.h"
#include"../App/stage/Stage.h"
StageSelect::StageSelect()
{}
StageSelect::~StageSelect()
{
}
void StageSelect::Initialize()
{
	m_selectOBJ = Shape::CreateOBJ("cube");
	m_boxBreakOBJ = Shape::CreateRect(30.0f, 30.0f);

	m_selectGraph[0] = Texture::Get()->LoadTexture(L"Resources/select/select1.png");
	m_selectGraph[1] = Texture::Get()->LoadTexture(L"Resources/select/select2.png");
	m_selectGraph[2] = Texture::Get()->LoadTexture(L"Resources/select/select3.png");

	m_boxFramGraph = Texture::Get()->LoadTexture(L"Resources/select/selectFram.png");
	m_boxBreakGraph = Texture::Get()->LoadTexture(L"Resources/UI/UIBox.png");
	// ライトグループクラス作成
	lightGroup = std::make_unique<LightGroup>();
	lightGroup->Initialize();
	// 3Dオブエクトにライトをセット
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightDir(0, XMVECTOR{ 0,0,1,0 });
	lightGroup->SetShadowDir(Vec3(0, 1, -1));
	m_boxSE = Audio::SoundLoadWave("Resources/sound/SE/boxBreak.wav");


	m_numberGraph[0] = Texture::Get()->LoadTexture(L"Resources/UI/UINumber1.png");
	m_numberGraph[1] = Texture::Get()->LoadTexture(L"Resources/UI/UINumber2.png");
	m_numberGraph[2] = Texture::Get()->LoadTexture(L"Resources/UI/UINumber3.png");
	m_numberGraph[3] = Texture::Get()->LoadTexture(L"Resources/UI/UINumber4.png");
	m_numberGraph[4] = Texture::Get()->LoadTexture(L"Resources/UI/UINumber5.png");
	m_numberGraph[5] = Texture::Get()->LoadTexture(L"Resources/UI/UINumber6.png");
	m_numberGraph[6] = Texture::Get()->LoadTexture(L"Resources/UI/UINumber7.png");
	m_numberGraph[7] = Texture::Get()->LoadTexture(L"Resources/UI/UINumber8.png");
	m_numberGraph[8] = Texture::Get()->LoadTexture(L"Resources/UI/UINumber9.png");
	m_numberGraph[9] = Texture::Get()->LoadTexture(L"Resources/UI/UINumber10.png");
	m_numberGraph[10] = Texture::Get()->LoadTexture(L"Resources/UI/UISlash.png");
}

void StageSelect::Init()
{
	FBXObject3d::SetLight(lightGroup.get());
	Object::SetLight(lightGroup.get());
	Player::Get()->SetMoveFlag(false);
	Player::Get()->Reset();
	Player::Get()->GetClearFlag(false);
	for (size_t i = 0; i < c_stageNumMax; i++)
	{
		m_selectPos[i] = Vec3(50.0f + 50 * i, 30.0f, 150.0f);
		m_selectBox[i].maxPosition = XMVectorSet(m_selectPos[i].x + c_selectScale / 2, m_selectPos[i].y + c_selectScale / 2, m_selectPos[i].z + c_selectScale / 2, 1);
		m_selectBox[i].minPosition = XMVectorSet(m_selectPos[i].x - c_selectScale / 2, m_selectPos[i].y - c_selectScale / 2, m_selectPos[i].z - c_selectScale / 2, 1);
	}
	m_selectFlag = false;
	Stage::Get()->LoadStage(0);
	Player::Get()->SetPosition(Vec3(20.0f, 10.0f, 150.0f));

	//演出初期化
	for (int i = 0; i < c_stageNumMax; i++)
	{
		m_productionFlag[i] = false;
	}
	m_productionTime = 0;
}


void StageSelect::Update()
{
	//ステージ選択
	Camera::Get()->FollowCamera(Player::Get()->GetPosition(), Vec3(0.0f, 15.0f, -130.0f));

	for (int i = 0; i < c_stageNumMax; i++)
	{
		if (Collision::CheckBox2Box(Player::Get()->GetBox(), m_selectBox[i]))
		{
			if (m_selectPos[i].y - c_selectScale / 2 > Player::Get()->GetOldPosition().y + Player::Get()->GetPSize().y / 2 && m_productionTime == 0)
			{
				m_stageNum = i + 1;
				m_productionFlag[i] = true;
				m_productionTime = c_productionTimeMax;
				Player::Get()->JumpPoweZero();
				Audio::Get()->SoundSEPlayWave(m_boxSE);
			}
			else
			{
				Player::Get()->SetPosition(Vec3(Player::Get()->GetOldPosition().x, Player::Get()->GetPosition().y, Player::Get()->GetPosition().z));
			}
		}
	}

	if (m_productionFlag[0] == true || m_productionFlag[1] == true || m_productionFlag[2] == true)
	{
		Player::Get()->DieType(1);
		Player::Get()->JumpPoweZero();
	}

	Player::Get()->Update();

	Stage::Get()->Update(Player::Get()->GetPosition());
	//ライト更新
	lightGroup->Update();

	//箱が上に上がる演出
	for (int i = 0; i < c_stageNumMax; i++)
	{
		if (m_productionFlag[i] == true && m_productionTime > 0)
		{
			m_productionTime--;

			if (m_productionTime > c_productionTimeMax - 10)
			{
				m_selectPos[i].y += 1.0f;
			}
			else if (m_productionTime > c_productionTimeMax - 20)
			{
				m_selectPos[i].y -= 1.0f;
			}

			if (m_productionTime <= 0)
			{
				m_selectFlag = true;
			}
		}
	}


	//最大箱の数
	for (int i = 0; i < 3; i++)
	{
		m_breakNumMax[i] = c_breakBoxMax[i] % 10;
		m_breakNumTenMax[i] = c_breakBoxMax[i] / 10;


		m_breakNum[i] = m_breakBox[i] % 10;
		m_breakNumTen[i] = m_breakBox[i] / 10;
	}
}

void StageSelect::Draw()
{
	//背景描画
	Player::Get()->Draw(true);
	Stage::Get()->Draw(Player::Get()->GetPosition(), true);
	for (size_t i = 0; i < c_stageNumMax; i++)
	{
		Object::NoShadowDraw(m_boxBreakOBJ, m_flamePSR[i], Vec3(50.0f + 50 * i, 50.0f, 150.0f),
			Vec3(1.3f, 1.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec2(), m_boxFramGraph);
		Object::NoShadowDraw(m_boxBreakOBJ, m_boxBreakPSR[i], Vec3(40.0f + 50 * i, 50.0f, 149.5f),
			Vec3(0.4f, 0.4f, 0.4f), Vec3(0.0f, 0.0f, 0.0f), Vec2(), m_boxBreakGraph);
		//数字十の桁
		Object::NoShadowDraw(m_boxBreakOBJ, m_boxBreakPSR[i], Vec3(48.0f + 50 * i, 57.0f, 149.5f),
			Vec3(0.3f, 0.3f, 0.3f), Vec3(0.0f, 0.0f, 0.0f), Vec2(), m_numberGraph[m_breakNumTen[i]]);
		//数字一の桁
		Object::NoShadowDraw(m_boxBreakOBJ, m_boxBreakPSR[i], Vec3(56.0f + 50 * i, 57.0f, 149.5f),
			Vec3(0.3f, 0.3f, 0.3f), Vec3(0.0f, 0.0f, 0.0f), Vec2(), m_numberGraph[m_breakNum[i]]);
		//最大数字十の桁
		Object::NoShadowDraw(m_boxBreakOBJ, m_boxBreakPSR[i], Vec3(53.0f + 50 * i, 42.0f, 149.5f),
			Vec3(0.3f, 0.3f, 0.3f), Vec3(0.0f, 0.0f, 0.0f), Vec2(), m_numberGraph[m_breakNumTenMax[i]]);
		//最大数字一の桁
		Object::NoShadowDraw(m_boxBreakOBJ, m_boxBreakPSR[i], Vec3(60.0f + 50 * i, 42.0f, 149.5f),
			Vec3(0.3f, 0.3f, 0.3f), Vec3(0.0f, 0.0f, 0.0f), Vec2(), m_numberGraph[m_breakNumMax[i]]);

		Object::NoShadowDraw(m_boxBreakOBJ, m_boxBreakPSR[i], Vec3(54.0f + 50 * i, 50.0f, 149.0f),
			Vec3(0.3f, 0.3f, 0.3f), Vec3(0.0f, 0.0f, 0.0f), Vec2(), m_numberGraph[10]);

		Object::Draw(m_selectOBJ, m_selectPsr[i], m_selectPos[i],
			Vec3(c_selectScale, c_selectScale, c_selectScale), Vec3(), Vec2(), m_selectGraph[i], true);
	}
}

void StageSelect::DrawShadow()
{
	Player::Get()->Draw();
	Stage::Get()->Draw(Player::Get()->GetPosition());
}

void StageSelect::SetBreakBoxNum(int breakBox_)
{
	if (breakBox_ > m_breakBox[m_stageNum - 1])
	{
		m_breakBox[m_stageNum - 1] = breakBox_;
	}

}
