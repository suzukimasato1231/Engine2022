#include"TitleScene.h"
#include<sstream>
#include<iomanip>
#include"Camera.h"
#include"Shape.h"
#include"Input.h"
#include"Texture.h"

TitleScene::TitleScene()
{}
TitleScene::~TitleScene()
{
}
void TitleScene::Initialize()
{
	titlePlayer = Shape::CreateOBJ("pengin", true);
	box = Shape::CreateOBJ("cube");
	boxGraph = Texture::Get()->LoadTexture(L"Resources/cube/Normal.png");
	titleButtonGraph = Sprite::Get()->SpriteCreate(L"Resources/titleButton.png");
	titleGraph = Sprite::Get()->SpriteCreate(L"Resources/Title.png");

	wallObj = Shape::CreateOBJ("iceWall");
	floorObj = Shape::CreateOBJ("ice");

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
	Object::Draw(titlePlayer, titlePsr, Vec3(10.0f, -3.5f, 0.0f), Vec3(1, 1, 1),
		Vec3(0.0f, 10.0f, 0.0f), Vec4(), titlePlayer.OBJTexture, true);

	Object::Draw(box, boxPsr, Vec3(10.0f, 5.0f, 0.0f), Vec3(2, 2, 2),
		Vec3(0.0f, 10.0f, 0.0f), Vec4(), boxGraph, true);

	Object::Draw(floorObj, wallPsr, Vec3(0.0f, -5.0f, 0.0f), Vec3(1000.0f, 1.0f, 1000.0f),
		Vec3(), Vec4(), floorObj.OBJTexture, true);

	Object::Draw(floorObj, wallPsr, Vec3(0.0f, 5.0f, 20.0f), Vec3(100.0f, 20.0f, 10.0f),
		Vec3(), Vec4(), floorObj.OBJTexture, true);

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
	Object::Draw(titlePlayer, titlePsr, Vec3(10.0f, -3.5f, 0.0f), Vec3(1, 1, 1),
		Vec3(0.0f, 10.0f, 0.0f), Vec4(), titlePlayer.OBJTexture);
	Object::Draw(box, boxPsr, Vec3(10.0f, 5.0f, 0.0f), Vec3(2, 2, 2),
		Vec3(0.0f, 10.0f, 0.0f), Vec4(), boxGraph);
	Object::Draw(floorObj, wallPsr, Vec3(0.0f, -5.0f, 0.0f), Vec3(1000.0f, 1.0f, 1000.0f),
		Vec3(), Vec4());
}
