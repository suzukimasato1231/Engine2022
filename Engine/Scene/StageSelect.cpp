#include "StageSelect.h"
#include<sstream>
#include<iomanip>
#include "Input.h"
#include"Shape.h"
#include"DebugText.h"
#include"../Player.h"
#include"Object.h"
#include"../Stage.h"
StageSelect::StageSelect()
{}
StageSelect::~StageSelect()
{
	safe_delete(lightGroup);
}
void StageSelect::Initialize()
{
	selectOBJ = Shape::CreateSquare(10.0f, 10.0f, 10.0f);
	selectGraph[0] = Texture::Get()->LoadTexture(L"Resources/select/select1.png");
	selectGraph[1] = Texture::Get()->LoadTexture(L"Resources/select/select2.png");

	// ライトグループクラス作成
	lightGroup = LightGroup::Create();
	//音データ読み込み
	// 3Dオブエクトにライトをセット
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightDir(0, XMVECTOR{ 0,0,-1,0 });
	lightGroup->SetShadowDir(Vec3(0, 1, 0));
}

void StageSelect::Init()
{
	FBXObject3d::SetLight(lightGroup);
	Object::SetLight(lightGroup);

	Player::Get()->ChangeMoveFlag(false);
	for (size_t i = 0; i < stageNumMax; i++)
	{
		selectPos[i] = Vec3(50.0f + 50 * i, 30.0f, 150.0f);
		selectBox[i].maxPosition = XMVectorSet(selectPos[i].x + selectScale / 2, selectPos[i].y + selectScale / 2, selectPos[i].z + selectScale / 2, 1);
		selectBox[i].minPosition = XMVectorSet(selectPos[i].x - selectScale / 2, selectPos[i].y - selectScale / 2, selectPos[i].z - selectScale / 2, 1);
	}
	selectFlag = false;
	Stage::Get()->LoadStage(0);
	Player::Get()->SetPosition(Vec3(20.0f, 10.0f, 150.0f));
}

void StageSelect::Update()
{
	//ステージ選択
	Camera::Get()->FollowCamera(Player::Get()->GetPosition(), Vec3(0.0f, 5.0f, -100.0f));

	for (int i = 0; i < stageNumMax; i++)
	{
		if (Collision::CheckBox2Box(Player::Get()->GetBox(), selectBox[i]))
		{
			stageNum = i + 1;
			selectFlag = true;
			break;
		}
	}
	Player::Get()->Update();
	Stage::Get()->Update(Player::Get()->GetPosition());
	//ライト更新
	lightGroup->Update();
}

void StageSelect::Draw()
{
	//背景描画
	Player::Get()->Draw(true);
	Stage::Get()->Draw(Player::Get()->GetPosition(), true);
	for (size_t i = 0; i < stageNumMax; i++)
	{
		Object::Draw(selectOBJ,selectPsr[i], selectPos[i], Vec3(1.0f, 1.0f, 1.0f), Vec3(), Vec4(), selectGraph[i], true);
	}
}

void StageSelect::DrawShadow()
{
	Player::Get()->Draw();
	Stage::Get()->Draw(Player::Get()->GetPosition());
}
