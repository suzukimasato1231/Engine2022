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
	m_boxGraph = Sprite::Get()->SpriteCreate(L"Resources/UI/UIBox.png");
	m_uiNumber[0] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber1.png");
	m_uiNumber[1] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber2.png");
	m_uiNumber[2] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber3.png");
	m_uiNumber[3] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber4.png");
	m_uiNumber[4] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber5.png");
	m_uiNumber[5] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber6.png");
	m_uiNumber[6] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber7.png");
	m_uiNumber[7] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber8.png");
	m_uiNumber[8] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber9.png");
	m_uiNumber[9] = Sprite::Get()->SpriteCreate(L"Resources/UI/UINumber10.png");
	m_uiSlash = Sprite::Get()->SpriteCreate(L"Resources/UI/UISlash.png");

	m_clearGraph = Sprite::Get()->SpriteCreate(L"Resources/UI/clear.png");
	m_nextGraph = Sprite::Get()->SpriteCreate(L"Resources/UI/retry.png");
	m_selectGraph = Sprite::Get()->SpriteCreate(L"Resources/UI/select.png");

	m_buttonGraph = Sprite::Get()->SpriteCreate(L"Resources/UI/titleButton.png");


	Model* model1 = FbxLoader::GetInstance()->LoadModelFromFile("movePengin", "FBX/");
	m_penginModel = std::make_unique<Model>();
	m_penginModel = std::unique_ptr<Model>(model1);
	//3Dオブジェクトの生成とモデルのセット
	m_penginHandFbx = std::make_unique<FBXObject3d>();
	m_penginHandFbx->Initialize();
	m_penginHandFbx->SetModel(m_penginModel.get());
	m_penginHandFbx->SetScale(fbxScale);

	m_fishObj = Shape::CreateOBJ("fish", false, "OBJ/");
	m_floorObj = Shape::CreateOBJ("ice", false, "OBJ/");
	// ライトグループクラス作成
	lightGroup = std::make_unique<LightGroup>();
	lightGroup->Initialize();
	// 3Dオブエクトにライトをセット
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightDir(0, XMVECTOR{ 0,-1,0,0 });
	lightGroup->SetShadowDir(Vec3(0, 1, 0));

	m_decisionSE = Audio::SoundLoadWave("Resources/sound/SE/menu.wav");
	m_selectSE = Audio::SoundLoadWave("Resources/sound/SE/menuSelect.wav");
}
void ResultScene::Init()
{
	m_resultTime = 0;
	Camera::Get()->SetCamera(Vec3{ 0,0,-15 }, Vec3{ 0, -3, 0 }, Vec3{ 0, 1, 0 });
	FBXObject3d::SetLight(lightGroup.get());
	Object::SetLight(lightGroup.get());
	m_penginHandFbx->PlayAnimation(true);
}

void ResultScene::Update()
{
	//順番にリザルトが出るように
	if (m_resultTime <= c_resultTimeMax)
	{
		m_resultTime++;
	}
	//ボタンの点滅
	m_buttonTime++;
	if (m_buttonTime >= c_buttonMax)
	{
		m_buttonTime = 0;
	}

	//次のシーン
	if (Input::Get()->ControllerDown(LButtonLeft) || Input::Get()->ControllerDown(LButtonRight))
	{
		if (m_nextScene == static_cast<int>(ResultNext::ResultNextStage))
		{
			m_nextScene = static_cast<int>(ResultNext::ResultSelect);
		}
		else
		{
			m_nextScene = static_cast<int>(ResultNext::ResultNextStage);
		}
		Audio::Get()->SoundSEPlayWave(m_selectSE);
	}
	//選択した方の大きさを変える
	if (m_nextScaleFlag == false)
	{
		m_nextScale += c_selectScaleSpeed;
		if (m_nextScale >= c_nextScaleMax)
		{
			m_nextScaleFlag = true;
		}
	}
	else
	{
		m_nextScale -= c_selectScaleSpeed;
		if (m_nextScale <= c_nextScaleMin)
		{
			m_nextScaleFlag = false;
		}
	}

	lightGroup->Update();
}

void ResultScene::Draw(const int stageNum)
{
	m_penginHandFbx->Draw(true);

	Object::Draw(m_floorObj, m_objectPsr, Vec3(0.0f, -5.0f, 0.0f),
		Vec3(1000.0f, 1.0f, 1000.0f), Vec3(), Vec2(), m_floorObj.OBJTexture, true);
	Object::Draw(m_floorObj, m_objectPsr, Vec3(0.0f, 5.0f, 20.0f), Vec3(100.0f, 20.0f, 10.0f),
		Vec3(), Vec2(), m_floorObj.OBJTexture, true);

	if (m_resultTime >= c_clearTimeMax)
	{
		Sprite::Get()->Draw(m_clearGraph, Vec2(), static_cast<float>(window_width), static_cast<float>(window_height));
	}
	//UI
	if (m_resultTime >= c_numberTime)
	{
		//箱
		Sprite::Get()->Draw(m_boxGraph, Vec2(300.0f, 200.0f), 150.0f, 150.0f);
		//壊した箱の数
		int Breaknumber = Stage::Get()->GetBlockNum() % 10, Breakremain = Stage::Get()->GetBlockNum() / 10;
		if (Breakremain >= 1)
		{
			Sprite::Get()->Draw(m_uiNumber[Breakremain], Vec2(450.0f, 200.0f), numberScale, numberScale);
		}
		Sprite::Get()->Draw(m_uiNumber[Breaknumber], Vec2(550.0f, 200.0f), numberScale, numberScale);

		Sprite::Get()->Draw(m_uiSlash, Vec2(650.0f, 200.0f), 128.0f, 128.0f);
		//最大箱の数
		Breaknumber = Stage::Get()->GetBlockMax() % 10, Breakremain = Stage::Get()->GetBlockMax() / 10;
		if (Breakremain >= 1)
		{
			Sprite::Get()->Draw(m_uiNumber[Breakremain], Vec2(750.0f, 200.0f), numberScale, numberScale);
		}
		Sprite::Get()->Draw(m_uiNumber[Breaknumber], Vec2(850.0f, 200.0f), numberScale, numberScale);
	}

	//セレクト
	const Vec2 anchorpoint = { 0.5f,0.5f };      //アンカーポイント
	const float basicPosY = 450.0f;              //数字のY軸の基本値
	const float basicPosX[2] = { 385.0f,987.0f };//数字X軸の基本値
	if (stageNum == stageMax)
	{
		Sprite::Get()->Draw(m_selectGraph, Vec2(687.0f, basicPosY + numberScale / 2),
			334.0f * m_nextScale, numberScale * m_nextScale, anchorpoint);
	}
	else
	{
		if (m_nextScene == static_cast<int>(ResultNext::ResultSelect))
		{
			Sprite::Get()->Draw(m_nextGraph, Vec2(basicPosX[0], basicPosY + numberScale / 2),
				533.0f, numberScale, anchorpoint);
			Sprite::Get()->Draw(m_selectGraph, Vec2(basicPosX[1], basicPosY + numberScale / 2),
				334.0f * m_nextScale, numberScale * m_nextScale, anchorpoint);
		}
		else
		{
			Sprite::Get()->Draw(m_nextGraph, Vec2(basicPosX[0], basicPosY + numberScale / 2),
				533.0f * m_nextScale, numberScale * m_nextScale, anchorpoint);
			Sprite::Get()->Draw(m_selectGraph, Vec2(basicPosX[1], basicPosY + numberScale / 2),
				334.0f, numberScale, anchorpoint);
		}
	}
	if (m_resultTime >= 90 && m_buttonTime >= 30)
	{
		Sprite::Get()->Draw(m_buttonGraph, Vec2(420.0f, 632.0f), 512.0f, 64.0f);
	}
}

void ResultScene::ShadowDraw()
{
	m_penginHandFbx->SetPosition(Vec3(8.0f, -4.5f, 0.0f));
	m_penginHandFbx->SetRotation(Vec3(-30.0f, 180.0f, 0.0f));
	m_penginHandFbx->Update();
	m_penginHandFbx->Draw();

	Object::Draw(m_floorObj, m_objectPsr, Vec3(0.0f, -5.0f, 0.0f),
		Vec3(1000.0f, 1.0f, 1000.0f), Vec3());
	Object::Draw(m_floorObj, m_objectPsr, Vec3(0.0f, 5.0f, 20.0f),
		Vec3(100.0f, 20.0f, 10.0f), Vec3(), Vec2(), m_floorObj.OBJTexture);
}
