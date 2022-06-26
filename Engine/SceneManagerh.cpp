#include "SceneManagerh.h"
#include<sstream>
#include<iomanip>
#include "Input.h"
#include"Shape.h"
SceneManagerh::SceneManagerh()
{}
SceneManagerh::~SceneManagerh()
{
	safe_delete(postEffect);
}
void SceneManagerh::Initialize()
{
	//汎用機能
	//ゲームウィンドウの作成
	_Window::Instance()->CreateGameWindow();
	// DirectX初期化処理
	_DirectX::Instance()->Initilize();
	//入力の初期化
	Input::Instance()->Initialize();
	//FBX初期化
	FbxLoader::GetInstance()->Initialize(_DirectX::Instance()->GetDevice());
	//ライト静的初期化
	LightGroup::StaticInitialize(_DirectX::Instance()->GetDevice());
	//スプライト静的初期化
	Sprite::StaticInit(_DirectX::Instance()->GetDevice(), _DirectX::Instance()->GetCmandList());
	//テキストクラス初期化
	Texture::Instance()->Init(_DirectX::Instance()->GetDevice());
	//デバックテキスト初期化
	DebugText::Instance()->Initialize();
	//スプライトクラス作成
	Sprite::Instance()->Init();
	//FBX初期化
	FBXObject3d::SetDevice(_DirectX::Instance()->GetDevice());
	FBXObject3d::SetCmdList(_DirectX::Instance()->GetCmandList());
	FBXObject3d::CreateGraphicsPipeline();
	//図形モデル初期化
	Shape::Init(_DirectX::Instance()->GetDevice());
	//パーティクル初期化
	ParticleManager::StaticInitialize(_DirectX::Instance()->GetDevice(), _DirectX::Instance()->GetCmandList(), window_width, window_height);
	//3Dオブジェクト初期化
	Object::Init(_DirectX::Instance()->GetDevice(), _DirectX::Instance()->GetCmandList());
	//ゲームシーン
	GameSceneManager::Instance()->Initialize();
	GameSceneManager::Instance()->Init();

	TitleScene::Instance()->Initialize();
	TitleScene::Instance()->Init();

	postEffect = new PostEffect;
	postEffect->Initialize(_DirectX::Instance()->GetDevice());

}

void SceneManagerh::Update()
{


	Input::Instance()->Update();

	if (scene == Title)
	{
		if (Input::Instance()->KeybordTrigger(DIK_SPACE))
		{
			scene = GameScene;
			GameSceneManager::Instance()->Init();
		}
	}
	else if (scene == GameScene)
	{
		
	}

	if (scene == Title)
	{
		TitleScene::Instance()->Update();
	}
	else if (scene == GameScene)
	{
		GameSceneManager::Instance()->Update();
	}


}

void SceneManagerh::Draw()
{
	//描画開始

	//オブジェクト描画前処理
	Object::Instance()->PreDraw();
	Sprite::Instance()->PreDraw();
	postEffect->PreDrawScene(_DirectX::Instance()->GetCmandList());
	if (scene == Title)
	{
		TitleScene::Instance()->Draw();
	}
	else if (scene == GameScene)
	{
		GameSceneManager::Instance()->Draw();
	}

	DebugText::Instance()->DrawAll();
	postEffect->PostDrawScene(_DirectX::Instance()->GetCmandList());

	_DirectX::Instance()->PreDraw();
	//ポストエフェクトの描画
	postEffect->Draw(_DirectX::Instance()->GetCmandList());
	_DirectX::Instance()->ResourceBarrier();
}
