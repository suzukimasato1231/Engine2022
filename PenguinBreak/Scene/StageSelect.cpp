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
	selectOBJ = Shape::CreateOBJ("cube");
	selectGraph[0] = Texture::Get()->LoadTexture(L"Resources/select/select1.png");
	selectGraph[1] = Texture::Get()->LoadTexture(L"Resources/select/select2.png");
	selectGraph[2] = Texture::Get()->LoadTexture(L"Resources/select/select3.png");
	// ライトグループクラス作成
	lightGroup = std::make_unique<LightGroup>();
	lightGroup->Initialize();
	// 3Dオブエクトにライトをセット
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightDir(0, XMVECTOR{ 0,0,1,0 });
	lightGroup->SetShadowDir(Vec3(0, 1, -1));
}

void StageSelect::Init()
{
	FBXObject3d::SetLight(lightGroup.get());
	Object::SetLight(lightGroup.get());
	Player::Get()->ChangeMoveFlag(false);
	Player::Get()->Reset();
	Player::Get()->GetClearFlag(false);
	for (size_t i = 0; i < stageNumMax; i++)
	{
		selectPos[i] = Vec3(50.0f + 50 * i, 30.0f, 150.0f);
		selectBox[i].maxPosition = XMVectorSet(selectPos[i].x + selectScale / 2, selectPos[i].y + selectScale / 2, selectPos[i].z + selectScale / 2, 1);
		selectBox[i].minPosition = XMVectorSet(selectPos[i].x - selectScale / 2, selectPos[i].y - selectScale / 2, selectPos[i].z - selectScale / 2, 1);
	}
	selectFlag = false;
	Stage::Get()->LoadStage(0);
	Player::Get()->SetPosition(Vec3(20.0f, 10.0f, 150.0f));

	//演出初期化
	for (int i = 0; i < stageNumMax; i++)
	{
		productionFlag[i] = false;
	}
	productionTime = 0;
}


void StageSelect::Update()
{
	//ステージ選択
	Camera::Get()->FollowCamera(Player::Get()->GetPosition(), Vec3(0.0f, 5.0f, -100.0f));

	for (int i = 0; i < stageNumMax; i++)
	{
		if (Collision::CheckBox2Box(Player::Get()->GetBox(), selectBox[i]))
		{
			if (selectPos[i].y - selectScale / 2 > Player::Get()->GetOldPosition().y + Player::Get()->GetPSize().y / 2 && productionTime == 0)
			{
				stageNum = i + 1;
				productionFlag[i] = true;
				productionTime = productionTimeMax;
				Player::Get()->JumpPoweZero();
			}
			else
			{
				Player::Get()->SetPosition(Vec3(Player::Get()->GetOldPosition().x, Player::Get()->GetPosition().y, Player::Get()->GetPosition().z));
			}
		}
	}

	if (productionFlag[0] == true || productionFlag[1] == true || productionFlag[2] == true)
	{
		Player::Get()->DieType(1);
		Player::Get()->JumpPoweZero();
	}

	Player::Get()->Update();

	Stage::Get()->Update(Player::Get()->GetPosition());
	//ライト更新
	lightGroup->Update();

	//箱が上に上がる演出
	for (int i = 0; i < stageNumMax; i++)
	{
		if (productionFlag[i] == true && productionTime > 0)
		{
			productionTime--;

			if (productionTime > productionTimeMax - 10)
			{
				selectPos[i].y += 1.0f;
			}
			else if (productionTime > productionTimeMax - 20)
			{
				selectPos[i].y -= 1.0f;
			}

			if (productionTime <= 0)
			{
				selectFlag = true;
			}
		}
	}
}

void StageSelect::Draw()
{
	//背景描画
	Player::Get()->Draw(true);
	Stage::Get()->Draw(Player::Get()->GetPosition(), true);
	for (size_t i = 0; i < stageNumMax; i++)
	{
		Object::Draw(selectOBJ, selectPsr[i], selectPos[i], Vec3(selectScale, selectScale, selectScale), Vec3(), Vec2(), selectGraph[i], true);
	}
}

void StageSelect::DrawShadow()
{
	Player::Get()->Draw();
	Stage::Get()->Draw(Player::Get()->GetPosition());
}
