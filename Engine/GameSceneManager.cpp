#include "GameSceneManager.h"
#include<sstream>
#include<iomanip>
#include "Input.h"
#include"FbxLoader.h"
#include"Shape.h"
#include"Particle.h"
#include"Particle.h"
GameSceneManager::GameSceneManager()
{}
GameSceneManager::~GameSceneManager()
{
	//safe_delete(particleMan);
	safe_delete(lightGroup);
	safe_delete(fbxObject1);
	safe_delete(model1);
	safe_delete(enemy);
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
	Stage::Instance()->Init();
}

void GameSceneManager::Init()
{
	FBXObject3d::SetCamera(camera);
	ParticleManager::SetCamera(camera);
	Object::SetCamera(camera);
	Object::SetLight(lightGroup);
	changeScene = false;
	Reset();
	Particle::Instance()->Init();
}

void GameSceneManager::Update()
{
	//プレイヤーの更新

	if (Input::Instance()->KeybordTrigger(DIK_R))
	{
		Reset();
		Stage::Instance()->MainInit(0);
	}

	Player::Instance()->Update(enemy);

	enemy->Update();

	Stage::Instance()->Update();

	//
	camera->FollowCamera(Player::Instance()->GetPosition(), Vec3{ 0,0,-100 }, 0.0f, 35.0f);

	//クリアしたらシーンチェンジ
	if (Stage::Instance()->GetClearFlag())
	{
		changeScene = true;
	}
	Particle::Instance()->Update();
	//ライト更新
	lightGroup->Update();
}

void GameSceneManager::Draw()
{
	//背景描画
	//Drawにカーソル合わせればコメントアウトしてあるからなにがどの変数かわかるよ
	//Sprite::Instance()->Draw(BGGraph, pos, (float)window_width, (float)window_height);



	Stage::Instance()->Draw();
	//プレイヤーの描画
	Player::Instance()->Draw();

	Particle::Instance()->Draw();

}

void GameSceneManager::Reset()
{
	Player::Instance()->Reset();
}
