#include "ResultScene.h"
#include"DebugText.h"
#include"../App/stage/Stage.h"
#include"Shape.h"
#include <FBXObject3d.h>
ResultScene::ResultScene()
{
}
ResultScene::~ResultScene()
{
	safe_delete(lightGroup);
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

	buttonGraph = Sprite::Get()->SpriteCreate(L"Resources/titleButton.png");

	fishObj = Shape::CreateOBJ("fish");
	penginObj = Shape::CreateOBJ("pengin");
	floorObj = Shape::CreateOBJ("ice");
	// ライトグループクラス作成
	lightGroup = LightGroup::Create();
	// 3Dオブエクトにライトをセット
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightDir(0, XMVECTOR{ 0,-1,0,0 });
	lightGroup->SetShadowDir(Vec3(0, 1, 0));
}
void ResultScene::Init()
{
	resultTime = 0;
	Camera::Get()->SetCamera(Vec3{ 0,0,-15 }, Vec3{ 0, -3, 0 }, Vec3{ 0, 1, 0 });
	FBXObject3d::SetLight(lightGroup);
	Object::SetLight(lightGroup);
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
	lightGroup->Update();
}

void ResultScene::Draw()
{
	Object::Draw(penginObj, objectPsr, Vec3(8.0f, -3.5f, 0.0f),
		Vec3(1.0f, 1.0f, 1.0f), Vec3(), Vec4(),penginObj.OBJTexture, true);
	Object::Draw(floorObj, objectPsr, Vec3(0.0f, -5.0f, 0.0f),
		Vec3(1000.0f, 1.0f, 1000.0f), Vec3(),Vec4(),floorObj.OBJTexture,true);
	Object::Draw(floorObj, objectPsr, Vec3(0.0f, 5.0f, 20.0f), Vec3(100.0f, 20.0f, 10.0f),
		Vec3(), Vec4(), floorObj.OBJTexture, true);
	//UI
	if (resultTime >= 30)
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
	if (resultTime >= 60 && buttonTime >= 30)
	{
		Sprite::Get()->Draw(buttonGraph, Vec2(420.0f, 532.0f), 512.0f, 64.0f);
	}
}

void ResultScene::ShadowDraw()
{
	Object::Draw(penginObj, objectPsr, Vec3(8.0f, -3.5f, 0.0f),
		Vec3(1.0f, 1.0f, 1.0f), Vec3());
	Object::Draw(floorObj, objectPsr, Vec3(0.0f, -5.0f, 0.0f),
		Vec3(1000.0f, 1.0f, 1000.0f), Vec3());
	Object::Draw(floorObj, objectPsr, Vec3(0.0f, 5.0f, 20.0f), Vec3(100.0f, 20.0f, 10.0f),
		Vec3(), Vec4(), floorObj.OBJTexture, true);
}
