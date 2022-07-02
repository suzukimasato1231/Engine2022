#include"TitleScene.h"
#include<sstream>
#include<iomanip>
#include "Input.h"
#include"Shape.h"

TitleScene::TitleScene()
{}
TitleScene::~TitleScene()
{
	safe_delete(lightGroup);
	safe_delete(camera);
	safe_delete(audio);
}
void TitleScene::Initialize()
{
	//Audioクラス作成
	audio = Audio::Create();
	//カメラクラス作成
	camera = Camera::Create();
	//ライトグループクラス作成
	lightGroup = LightGroup::Create();
	// 3Dオブエクトにライトをセット
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightDir(0, XMVECTOR{ 0,0,1,0 });
	lightGroup->SetDirLightActive(1, true);
	lightGroup->SetDirLightDir(1, XMVECTOR{ 0,-1,0,0 });
	lightGroup->SetPointLightActive(0, false);
	lightGroup->SetSpotLightActive(0, false);
	lightGroup->SetCircleShadowActive(0, false);
	//カメラ位置をセット
	camera->SetCamera(Vec3{ 0,0,-200 }, Vec3{ 0, 0, 0 }, Vec3{ 0, 1, 0 });
}

void TitleScene::Init()
{
	FBXObject3d::SetCamera(camera);
	ParticleManager::SetCamera(camera);
	Object::SetCamera(camera);
	Object::SetLight(lightGroup);
}

void TitleScene::Update()
{
	
}

void TitleScene::Draw()
{
	//背景描画
	DebugText::Instance()->Print(10.0f, 10.0f, 3, "Title");
}
