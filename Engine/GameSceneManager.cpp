#include "GameSceneManager.h"
#include<sstream>
#include<iomanip>
#include "Input.h"
#include"FbxLoader.h"
#include"Shape.h"

GameSceneManager::GameSceneManager()
{}
GameSceneManager::~GameSceneManager()
{
	safe_delete(particleMan);
	safe_delete(lightGroup);
	safe_delete(fbxObject1);
	safe_delete(model1);
	safe_delete(enemy);
	safe_delete(stage);
	//XAudio2解放
	audio->xAudio2.Reset();
	//音データ解放
	safe_delete(audio);
}
void GameSceneManager::Initialize()
{
	//Audioクラス作成
	audio = Audio::Create();
	//カメラクラス作成
	camera = Camera::Create();
	//パーティクルクラス作成
	particleMan = ParticleManager::Create();
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
	lightGroup->SetCircleShadowActive(0, false);
	//カメラ位置をセット
	camera->SetCamera(Vec3{ 0,0,-200 }, Vec3{ 0, 0, 0 }, Vec3{ 0, 1, 0 });
	//スプライト画像読み込み

	BGGraph = Sprite::Instance()->SpriteCreate(L"Resources/backgroundA.png");

	//3Dオブジェクト画像読み込み

	//モデル名を指定してファイル読み込み
	model1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
	//3Dオブジェクトの生成とモデルのセット
	fbxObject1 = new FBXObject3d;
	fbxObject1->Initialize();
	fbxObject1->SetModel(model1);
	//プレイヤーの初期化
	Player::Instance()->Init();
	//敵
	enemy = new Enemy;
	enemy->Init();
	//ステージ
	stage = new Stage;
	stage->Init();
}

void GameSceneManager::Init()
{
	FBXObject3d::SetCamera(camera);
	ParticleManager::SetCamera(camera);
	Object::SetCamera(camera);
	Object::SetLight(lightGroup);
	changeScene = false;
	Reset();
}

void GameSceneManager::Update()
{
	//プレイヤーの更新

	if (Input::Instance()->KeybordTrigger(DIK_R))
	{
		Reset();
	}

	Player::Instance()->Update(enemy);

	enemy->Update();

	stage->Update();

	//
	camera->FollowCamera(Player::Instance()->GetPosition(), Vec3{ 0,0,-100 }, 0.0f, 35.0f);



	//パーティクル更新
	particleMan->Update();
	//ライト更新
	lightGroup->Update();
	//クリアしたらシーンチェンジ
	if (stage->GetClearFlag())
	{
		changeScene = true;
	}
}

void GameSceneManager::Draw()
{
	//背景描画
	//Drawにカーソル合わせればコメントアウトしてあるからなにがどの変数かわかるよ
	//Sprite::Instance()->Draw(BGGraph, pos, (float)window_width, (float)window_height);

	//プレイヤーの描画
	Player::Instance()->Draw();

	stage->Draw();
}

void GameSceneManager::Reset()
{
	Player::Instance()->Reset();
}
