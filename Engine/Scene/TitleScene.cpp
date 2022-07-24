#include"TitleScene.h"
#include<sstream>
#include<iomanip>
#include"Camera.h"
#include"Shape.h"
#include"Input.h"
TitleScene::TitleScene()
{}
TitleScene::~TitleScene()
{
}
void TitleScene::Initialize()
{
	//ライトグループクラス作成
	lightGroup = LightGroup::Create();

	//音データ読み込み
	// 3Dオブエクトにライトをセット
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightDir(0, XMVECTOR{ 0,-1,0,0 });

	//カメラ位置をセット
	Camera::Get()->SetCamera(Vec3{ 0,50,-10 }, Vec3{ 0, 0, 0 }, Vec3{ 0, 1, 0 });

	floor = Shape::CreateSquare(200.0f, 2.0f, 200.0f);

	polygon = Shape::CreateOBJ("sphere",true);
}

void TitleScene::Init()
{
	Object::SetLight(lightGroup);
	//カメラ位置をセット
	Camera::Get()->SetCamera(Vec3{ 0,20,-40 }, Vec3{ 0, 0, 0 }, Vec3{ 0, 1, 0 });

}

void TitleScene::Update()
{
	if (Input::Get()->KeybordTrigger(DIK_LEFT))
	{
		pos.x -= 1.0f;
	}
	if (Input::Get()->KeybordTrigger(DIK_RIGHT))
	{
		pos.x += 1.0f;
	}
	if (Input::Get()->KeybordTrigger(DIK_DOWN))
	{
		pos.y -= 1.0f;
	}
	if (Input::Get()->KeybordTrigger(DIK_UP))
	{
		pos.y += 1.0f;
	}

	lightGroup->Update();
}

void TitleScene::Draw()
{
	Object::Get()->Draw(floor, Vec3(), Vec3(1.0f, 1.0f, 1.0f), Vec3());

	Object::Get()->Draw(polygon, pos, Vec3(1.0f, 1.0f, 1.0f), Vec3());

	Object::Get()->Draw(polygon, Vec3(10.0f, 20.0f, 20.0f), Vec3(1.0f, 1.0f, 1.0f), Vec3());

	Object::Get()->Draw(polygon, Vec3(0.0f, 20.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f), Vec3());
	//背景描画
	DebugText::Get()->Print(10.0f, 10.0f, 3, "Title");
}

void TitleScene::ShadowDraw()
{
	Object::Get()->Draw(floor, Vec3(), Vec3(1.0f, 1.0f, 1.0f), Vec3(), Vec4(), 0, true);

	Object::Get()->Draw(polygon, pos, Vec3(1.0f, 1.0f, 1.0f), Vec3(), Vec4(), 0, true);

	Object::Get()->Draw(polygon, Vec3(10.0f, 20.0f, 20.0f), Vec3(1.0f, 1.0f, 1.0f), Vec3(), Vec4(), 0, true);
}
