#include "ResultScene.h"
#include"DebugText.h"
#include"../App/stage/Stage.h"
#include"Shape.h"
#include <FBXObject3d.h>
#include<Input.h>
ResultScene::ResultScene()
{}
ResultScene::~ResultScene()
{

}
void ResultScene::Initialize()
{
	boxGraph = Sprite::Get()->SpriteCreate(L"Resources/UI/UIBox.png");
	uiNumber[0] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber1.png");
	uiNumber[1] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber2.png");
	uiNumber[2] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber3.png");
	uiNumber[3] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber4.png");
	uiNumber[4] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber5.png");
	uiNumber[5] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber6.png");
	uiNumber[6] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber7.png");
	uiNumber[7] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber8.png");
	uiNumber[8] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber9.png");
	uiNumber[9] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber10.png");
	uiSlash = Sprite::Get()->SpriteCreate(L"Resources/UI/UISlash.png");

	clearGraph = Sprite::Get()->SpriteCreate(L"Resources/clear.png");
	nextGraph = Sprite::Get()->SpriteCreate(L"Resources/resultUI/retry.png");
	selectGraph = Sprite::Get()->SpriteCreate(L"Resources/resultUI/select.png");

	buttonGraph = Sprite::Get()->SpriteCreate(L"Resources/titleButton.png");


	penginModel = FbxLoader::GetInstance()->LoadModelFromFile("movePengin", "FBX/");
	for (int i = 0; i < 2; i++)
	{
		//3Dオブジェクトの生成とモデルのセット
		penginHandFbx[i] = std::make_unique<FBXObject3d>();
		penginHandFbx[i]->Initialize();
		penginHandFbx[i]->SetModel(penginModel);
		penginHandFbx[i]->SetScale(Vec3(0.015f, 0.015f, 0.015f));
	}
	fishObj = Shape::CreateOBJ("fish");
	floorObj = Shape::CreateOBJ("ice");
	// ライトグループクラス作成
	lightGroup = std::make_unique<LightGroup>();
	lightGroup->Initialize();
	// 3Dオブエクトにライトをセット
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightDir(0, XMVECTOR{ 0,-1,0,0 });
	lightGroup->SetShadowDir(Vec3(0, 1, 0));
}
void ResultScene::Init()
{
	resultTime = 0;
	Camera::Get()->SetCamera(Vec3{ 0,0,-15 }, Vec3{ 0, -3, 0 }, Vec3{ 0, 1, 0 });
	FBXObject3d::SetLight(lightGroup.get());
	Object::SetLight(lightGroup.get());
	for (int i = 0; i < 2; i++)
	{
		penginHandFbx[i]->PlayAnimation(true);
	}
}

void ResultScene::Update()
{
	//順番にリザルトが出るように
	if (resultTime <= 500)
	{
		resultTime++;
	}
	//ボタンの点滅
	buttonTime++;
	if (buttonTime >= 60)
	{
		buttonTime = 0;
	}

	//次のシーン
	if (Input::Get()->ControllerDown(LButtonLeft) || Input::Get()->ControllerDown(LButtonRight))
	{
		if (nextScene == ResultNextStage)
		{
			nextScene = ResultSelect;
		}
		else
		{
			nextScene = ResultNextStage;
		}
	}
	//選択した方の大きさを変える
	if (nextScaleFlag == false)
	{
		nextScale += 0.02f;
		if (nextScale >= nextScaleMax)
		{
			nextScaleFlag = true;
		}
	}
	else
	{
		nextScale -= 0.02f;
		if (nextScale <= nextScaleMin)
		{
			nextScaleFlag = false;
		}
	}

	lightGroup->Update();
}

void ResultScene::Draw(const int stageNum)
{
	penginHandFbx[1]->SetPosition(Vec3(8.0f, -4.5f, 0.0f));
	penginHandFbx[1]->SetRotation(Vec3(-30.0f, 180.0f, 0.0f));
	penginHandFbx[1]->Update(false);
	penginHandFbx[1]->Draw();

	Object::Draw(floorObj, objectPsr, Vec3(0.0f, -5.0f, 0.0f),
		Vec3(1000.0f, 1.0f, 1000.0f), Vec3(), Vec2(), floorObj.OBJTexture, true);
	Object::Draw(floorObj, objectPsr, Vec3(0.0f, 5.0f, 20.0f), Vec3(100.0f, 20.0f, 10.0f),
		Vec3(), Vec2(), floorObj.OBJTexture, true);

	if (resultTime >= 30)
	{
		Sprite::Get()->Draw(clearGraph, Vec2(), static_cast<float>(window_width), static_cast<float>(window_height));
	}
	//UI
	if (resultTime >= 60)
	{
		//箱
		Sprite::Get()->Draw(boxGraph, Vec2(300.0f, 200.0f), 150.0f, 150.0f);
		//壊した箱の数
		int Breaknumber = Stage::Get()->GetBlockNum() % 10, Breakremain = Stage::Get()->GetBlockNum() / 10;
		if (Breakremain >= 1)
		{
			Sprite::Get()->Draw(uiNumber[Breakremain], Vec2(450.0f, 200.0f), 128.0f, 128.0f);
		}
		Sprite::Get()->Draw(uiNumber[Breaknumber], Vec2(550.0f, 200.0f), 128.0f, 128.0f);

		Sprite::Get()->Draw(uiSlash, Vec2(650.0f, 200.0f), 128.0f, 128.0f);
		//最大箱の数
		Breaknumber = Stage::Get()->GetBlockMax() % 10, Breakremain = Stage::Get()->GetBlockMax() / 10;
		if (Breakremain >= 1)
		{
			Sprite::Get()->Draw(uiNumber[Breakremain], Vec2(750.0f, 200.0f), 128.0f, 128.0f);
		}
		Sprite::Get()->Draw(uiNumber[Breaknumber], Vec2(850.0f, 200.0f), 128.0f, 128.0f);
	}

	//セレクト
	if (stageNum == 3)
	{
		Sprite::Get()->Draw(selectGraph, Vec2(520.0f + 334.0f / 2, 450.0f + 128.0f / 2), 334.0f * nextScale, 128.0f * nextScale, Vec2(0.5f, 0.5f));
	}
	else
	{
		if (nextScene == ResultSelect)
		{
			Sprite::Get()->Draw(nextGraph, Vec2(120.0f + 533.0f / 2, 450.0f + 128.0f / 2), 533.0f, 128.0f, Vec2(0.5f, 0.5f));
			Sprite::Get()->Draw(selectGraph, Vec2(820.0f + 334.0f / 2, 450.0f + 128.0f / 2), 334.0f * nextScale, 128.0f * nextScale, Vec2(0.5f, 0.5f));
		}
		else
		{
			Sprite::Get()->Draw(nextGraph, Vec2(120.0f + 533.0f / 2, 450.0f + 128.0f / 2), 533.0f * nextScale, 128.0f * nextScale, Vec2(0.5f, 0.5f));
			Sprite::Get()->Draw(selectGraph, Vec2(820.0f + 334.0f / 2, 450.0f + 128.0f / 2), 334.0f, 128.0f, Vec2(0.5f, 0.5f));
		}
	}
	if (resultTime >= 90 && buttonTime >= 30)
	{
		Sprite::Get()->Draw(buttonGraph, Vec2(420.0f, 632.0f), 512.0f, 64.0f);
	}
}

void ResultScene::Delete()
{
	safe_delete(penginModel);
}

void ResultScene::ShadowDraw()
{
	penginHandFbx[0]->SetPosition(Vec3(8.0f, -4.5f, 0.0f));
	penginHandFbx[0]->SetRotation(Vec3(-30.0f, 180.0f, 0.0f));
	penginHandFbx[0]->Update(true);
	penginHandFbx[0]->Draw();

	Object::Draw(floorObj, objectPsr, Vec3(0.0f, -5.0f, 0.0f),
		Vec3(1000.0f, 1.0f, 1000.0f), Vec3());
	Object::Draw(floorObj, objectPsr, Vec3(0.0f, 5.0f, 20.0f), Vec3(100.0f, 20.0f, 10.0f),
		Vec3(), Vec2(), floorObj.OBJTexture, true);
}
