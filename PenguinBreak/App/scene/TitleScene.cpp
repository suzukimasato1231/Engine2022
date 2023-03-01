#include"TitleScene.h"
#include<sstream>
#include<iomanip>
#include"Camera.h"
#include"Shape.h"
#include"Input.h"
#include"Texture.h"
#include"../App/player/Player.h"
TitleScene::TitleScene()
{}
TitleScene::~TitleScene()
{}
void TitleScene::Initialize()
{
	//画像をロード
	boxGraph = Texture::Get()->LoadTexture(L"Resources/cube/Normal.png");
	titleButtonGraph = Sprite::Get()->SpriteCreate(L"Resources/UI/titleButton.png");
	titleGraph = Sprite::Get()->SpriteCreate(L"Resources/Title.png");
	//オブジェクト読みこみ
	wallObj = Shape::CreateOBJ("iceWall", false, "OBJ/");
	floorObj = Shape::CreateOBJ("ice", false, "OBJ/");
	box = Shape::CreateOBJ("cube");
	Model* model1 = FbxLoader::GetInstance()->LoadModelFromFile("movePengin", "FBX/");
	penginModel = std::make_unique<Model>();
	penginModel = std::unique_ptr<Model>(model1);

	//3Dオブジェクトの生成とモデルのセット
	penginHandFbx = std::make_unique<FBXObject3d>();
	penginHandFbx->Initialize();
	penginHandFbx->SetModel(penginModel.get());
	penginHandFbx->SetScale(Vec3(0.015f, 0.015f, 0.015f));

	// ライトグループクラス作成
	lightGroup = std::make_unique<LightGroup>();
	lightGroup->Initialize();
	// 3Dオブエクトにライトをセット
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightDir(0, XMVECTOR{ 0,-1,0,0 });
	lightGroup->SetShadowDir(Vec3(0, 1, 0));
}


void TitleScene::Init()
{
	Camera::Get()->SetCamera(Vec3{ 0,0,-15 }, Vec3{ 0, -3, 0 }, Vec3{ 0, 1, 0 });
	FBXObject3d::SetLight(lightGroup.get());
	Object::SetLight(lightGroup.get());

	penginHandFbx->PlayAnimation(true);
}

void TitleScene::Update()
{
	buttonTime++;
	if (buttonTime >= 60)
	{
		buttonTime = 0;
	}
	lightGroup->Update();
}

void TitleScene::Draw()
{
	//3D
	penginHandFbx->Draw(true);
	Object::Draw(box, boxPsr, Vec3(10.0f, 5.0f, 0.0f), Vec3(2, 2, 2),
		Vec3(0.0f, 10.0f, 0.0f), Vec2(), boxGraph, true);

	Object::Draw(floorObj, wallPsr, Vec3(0.0f, -5.0f, 0.0f), Vec3(1000.0f, 1.0f, 1000.0f),
		Vec3(), Vec2(), floorObj.OBJTexture, true);

	Object::Draw(floorObj, wallPsr, Vec3(0.0f, 5.0f, 20.0f), Vec3(100.0f, 20.0f, 10.0f),
		Vec3(), Vec2(), floorObj.OBJTexture, true);

	//UI
	Sprite::Get()->Draw(titleGraph, Vec2(0.0f, 0.0f), static_cast<float>(window_width), static_cast<float>(window_height));
	if (buttonTime >= 30)
	{
		Sprite::Get()->Draw(titleButtonGraph, Vec2(420.0f, 532.0f), 512.0f, 64.0f);
	}
}

void TitleScene::ShadowDraw()
{
	//3D
	penginHandFbx->SetPosition(Vec3(8.0f, -4.5f, 0.0f));
	penginHandFbx->SetRotation(Vec3(-30.0f, 180.0f, 0.0f));
	penginHandFbx->Update();
	penginHandFbx->Draw();
	Object::Draw(box, boxPsr, Vec3(10.0f, 5.0f, 0.0f), Vec3(2, 2, 2),
		Vec3(0.0f, 10.0f, 0.0f), Vec2(), boxGraph);
	Object::Draw(floorObj, wallPsr, Vec3(0.0f, -5.0f, 0.0f), Vec3(1000.0f, 1.0f, 1000.0f),
		Vec3(), Vec2());
}