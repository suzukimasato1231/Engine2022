#include "GameSceneManager.h"
#include<sstream>
#include<iomanip>
#include "Input.h"
#include"FbxLoader.h"
#include"Shape.h"
#include"../Particle.h"
GameSceneManager::GameSceneManager()
{}
GameSceneManager::~GameSceneManager()
{
	safe_delete(lightGroup);
	safe_delete(fbxObject1);
	safe_delete(model1);
	//XAudio2解放
	audio->xAudio2.Reset();
	//音データ解放
	safe_delete(audio);
}
void GameSceneManager::Initialize()
{
	//Audioクラス作成
	audio = Audio::Create();
	//ライトグループクラス作成
	lightGroup = LightGroup::Create();
	//音データ読み込み
	// 3Dオブエクトにライトをセット
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightDir(0, XMVECTOR{ 0,-1,0,0 });
	lightGroup->SetShadowDir(Vec3(1, 1, 0));
	//カメラ位置をセット
	Camera::Get()->SetCamera(Vec3{ 0,0,-200 }, Vec3{ 0, 0, 0 }, Vec3{ 0, 1, 0 });
	//スプライト画像読み込み
	BGGraph = Sprite::Get()->SpriteCreate(L"Resources/backgroundA.png");
	BGGraph.texNumber = Texture::Get()->GetShadowTexture();
	//3Dオブジェクト画像読み込み
	//プレイヤーの初期化
	Player::Get()->Init();
	//ステージ
	Stage::Get()->Init();
	Particle::Get()->Init();
	TimeAttack::Get()->Init();
	UI::Get()->Init();
}

void GameSceneManager::Init(int stageNum)
{
	FBXObject3d::SetLight(lightGroup);
	Object::SetLight(lightGroup);
	changeScene = false;
	Reset(stageNum);
	this->stageNum = stageNum;
	Player::Get()->ChangeMoveFlag(true);
}

void GameSceneManager::Update()
{
	//プレイヤーの更新
	if (Input::Get()->KeybordTrigger(DIK_R))
	{
		Reset(stageNum);
	}
	Player::Get()->Update();

	Stage::Get()->Update(Player::Get()->GetPosition());
	//残機が０にならない限り追跡
	if (Player::Get()->GetGameoverFlag() == false)
	{
		Camera::Get()->FollowCamera(Player::Get()->GetPosition(), Vec3{ 0,0,-100 }, 0.0f, 45.0f);
	}
	//クリアしたらシーンチェンジ
	if (Stage::Get()->GetClearFlag() == true)
	{
		changeScene = true;
		changeNum = ChangeClear;
	}
	Particle::Get()->Update();
	//ライト更新
	lightGroup->Update();

	TimeAttack::Get()->Update();
	//ゲームオーバー時のセレクト
	if (Player::Get()->GetGameoverFlag() == true)
	{
		if (Input::Get()->KeybordTrigger(DIK_LEFT) == true || Input::Get()->ControllerDown(LButtonLeft) == true)
		{
			changeNum++;
		}
		if (Input::Get()->KeybordTrigger(DIK_RIGHT) == true || Input::Get()->ControllerDown(LButtonRight) == true)
		{
			changeNum--;
		}
		if (Input::Get()->KeybordTrigger(DIK_SPACE) == true || Input::Get()->ControllerDown(ButtonA) == true)
		{
			changeScene = true;
		}
		if (changeNum > 2)
		{
			changeNum = 1;
		}
		else if (changeNum < 1)
		{
			changeNum = 2;
		}
	}

	UI::Get()->Update();
}

void GameSceneManager::Draw()
{
	//背景描画
	//3D

	Stage::Get()->Draw(Player::Get()->GetPosition(), true);

	//プレイヤーの描画
	Player::Get()->Draw(true);

	Particle::Get()->Draw();

	//2D
	UI::Get()->Draw(Player::Get()->GetRemanLives(), Player::Get()->GetFishNum(),
		Player::Get()->GetGameoverFlag(), changeNum);
}

void GameSceneManager::ShadowDraw()
{
	Stage::Get()->Draw(Player::Get()->GetPosition());
	//プレイヤーの描画
	Player::Get()->Draw();
}

void GameSceneManager::Reset(int stageNum)
{
	Player::Get()->Reset();
	Stage::Get()->MainInit(stageNum);
	TimeAttack::Get()->Reset();
}

