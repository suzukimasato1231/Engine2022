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
	lightGroup->SetDirLightDir(0, XMVECTOR{ 0,0,1,0 });
	lightGroup->SetDirLightActive(1, true);
	lightGroup->SetDirLightDir(1, XMVECTOR{ 0,-1,0,0 });
	lightGroup->SetPointLightActive(0, false);
	lightGroup->SetSpotLightActive(0, false);
	//カメラ位置をセット
	Camera::Get()->SetCamera(Vec3{0,0,-200}, Vec3{0, 0, 0}, Vec3{0, 1, 0});
	//スプライト画像読み込み

	BGGraph = Sprite::Get()->SpriteCreate(L"Resources/backgroundA.png");


	//3Dオブジェクト画像読み込み
	//モデル名を指定してファイル読み込み
	//model1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
	//3Dオブジェクトの生成とモデルのセット
	//fbxObject1 = new FBXObject3d;
	//fbxObject1->Initialize();
	//fbxObject1->SetModel(model1);
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

	Stage::Get()->Update();

	//
	Camera::Get()->FollowCamera(Player::Get()->GetPosition(), Vec3{0,0,-100}, 0.0f, 35.0f);
	
	//クリアしたらシーンチェンジ
	if (Stage::Get()->GetClearFlag() == true)
	{
		changeScene = true;
	}
	Particle::Get()->Update();
	//ライト更新
	lightGroup->Update();

	TimeAttack::Get()->Update();

	UI::Get()->Update();
}

void GameSceneManager::Draw()
{
	//背景描画
	//Drawにカーソル合わせればコメントアウトしてあるからなにがどの変数かわかるよ
	//Sprite::Get()->Draw(BGGraph, pos, (float)window_width, (float)window_height);

	//3D

	Stage::Get()->Draw();
	//プレイヤーの描画
	Player::Get()->Draw();

	Particle::Get()->Draw();

	TimeAttack::Get()->Draw();

	//2D
	UI::Get()->Draw();
}

void GameSceneManager::Reset(int stageNum)
{
	Player::Get()->Reset();
	Stage::Get()->MainInit(stageNum);
	TimeAttack::Get()->Reset();
}
