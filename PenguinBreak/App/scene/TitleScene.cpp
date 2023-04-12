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

void TitleScene::Init(int stageNum)
{
	//画像をロード
	m_boxGraph = Texture::Get()->LoadTexture(L"Resources/cube/Normal.png");
	m_titleButtonGraph = Sprite::Get()->SpriteCreate(L"Resources/UI/titleButton.png");
	m_titleGraph = Sprite::Get()->SpriteCreate(L"Resources/Title.png");
	//オブジェクト読みこみ
	m_wallObj = Shape::CreateOBJ("iceWall", false, "OBJ/");
	m_floorObj = Shape::CreateOBJ("ice", false, "OBJ/");
	m_box = Shape::CreateOBJ("cube");
	Model* model1 = FbxLoader::GetInstance()->LoadModelFromFile("movePengin", "FBX/");
	m_penginModel = std::make_unique<Model>();
	m_penginModel = std::unique_ptr<Model>(model1);

	//3Dオブジェクトの生成とモデルのセット
	m_penginHandFbx = std::make_unique<FBXObject3d>();
	m_penginHandFbx->Initialize();
	m_penginHandFbx->SetModel(m_penginModel.get());
	m_penginHandFbx->SetScale(Vec3(0.015f, 0.015f, 0.015f));

	// ライトグループクラス作成
	lightGroup = std::make_unique<LightGroup>();
	lightGroup->Initialize();
	// 3Dオブエクトにライトをセット
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightDir(0, XMVECTOR{ 0,-1,0,0 });
	lightGroup->SetShadowDir(Vec3(0, 1, 0));

	Camera::Get()->SetCamera(Vec3{ 0,0,-15 }, Vec3{ 0, -3, 0 }, Vec3{ 0, 1, 0 });
	FBXObject3d::SetLight(lightGroup.get());
	Object::SetLight(lightGroup.get());

	m_penginHandFbx->PlayAnimation(true);
}

void TitleScene::Update(int& stageNum, const int m_breakBox[])
{
	m_buttonTime++;
	if (m_buttonTime >= 60)
	{
		m_buttonTime = 0;
	}
	lightGroup->Update();
}

void TitleScene::Draw(const int stageNum)
{
	//3D
	m_penginHandFbx->Draw(true);
	Object::Draw(m_box, m_boxPsr, Vec3(10.0f, 5.0f, 0.0f), Vec3(2, 2, 2),
		Vec3(0.0f, 10.0f, 0.0f), Vec2(), m_boxGraph, true);

	Object::Draw(m_floorObj, m_wallPsr, Vec3(0.0f, -5.0f, 0.0f), Vec3(1000.0f, 1.0f, 1000.0f),
		Vec3(), Vec2(), m_floorObj.OBJTexture, true);

	Object::Draw(m_floorObj, m_wallPsr, Vec3(0.0f, 5.0f, 20.0f), Vec3(100.0f, 20.0f, 10.0f),
		Vec3(), Vec2(), m_floorObj.OBJTexture, true);

	//UI
	Sprite::Get()->Draw(m_titleGraph, Vec2(0.0f, 0.0f), static_cast<float>(window_width), static_cast<float>(window_height));
	if (m_buttonTime >= 30)
	{
		Sprite::Get()->Draw(m_titleButtonGraph, Vec2(420.0f, 532.0f), 512.0f, 64.0f);
	}
}

void TitleScene::ShadowDraw()
{
	//3D
	m_penginHandFbx->SetPosition(Vec3(8.0f, -4.5f, 0.0f));
	m_penginHandFbx->SetRotation(Vec3(-30.0f, 180.0f, 0.0f));
	m_penginHandFbx->Update();
	m_penginHandFbx->Draw();
	Object::Draw(m_box, m_boxPsr, Vec3(10.0f, 5.0f, 0.0f), Vec3(2, 2, 2),
		Vec3(0.0f, 10.0f, 0.0f), Vec2(), m_boxGraph);
	Object::Draw(m_floorObj, m_wallPsr, Vec3(0.0f, -5.0f, 0.0f), Vec3(1000.0f, 1.0f, 1000.0f),
		Vec3(), Vec2());
}

void TitleScene::SecondDraw()
{}

void TitleScene::Finalize()
{}
