#include "SceneManagerh.h"
#include<sstream>
#include<iomanip>
#include "Input.h"
#include"Shape.h"
#include"PostEffect.h"
SceneManagerh::SceneManagerh()
{}
SceneManagerh::~SceneManagerh()
{
}
void SceneManagerh::Initialize()
{
	//汎用機能
	//ゲームウィンドウの作成
	_Window::Get()->CreateGameWindow();
	// DirectX初期化処理
	_DirectX::Get()->Initilize();
	//入力の初期化
	Input::Get()->Initialize();
	//シェーダーの読み込み
	ShaderManager::LoadShaders();
	//ライト静的初期化
	LightGroup::StaticInitialize(_DirectX::Get()->GetDevice());
	//スプライト静的初期化
	Sprite::StaticInit(_DirectX::Get()->GetDevice(), _DirectX::Get()->GetCmandList());
	//テキストクラス初期化
	Texture::Get()->Init(_DirectX::Get()->GetDevice());
	//デバックテキスト初期化
	DebugText::Get()->Initialize();
	//スプライトクラス作成
	Sprite::Get()->Init();
	//FBX初期化
	FbxLoader::GetInstance()->Initialize(_DirectX::Get()->GetDevice());
	FBXObject3d::SetDevice(_DirectX::Get()->GetDevice());
	FBXObject3d::SetCmdList(_DirectX::Get()->GetCmandList());
	FBXObject3d::CreateGraphicsPipeline();
	//図形モデル初期化
	Shape::Init(_DirectX::Get()->GetDevice());
	//パーティクル初期化
	ParticleManager::StaticInitialize(_DirectX::Get()->GetDevice(), _DirectX::Get()->GetCmandList(), window_width, window_height);
	//3Dオブジェクト初期化
	Object::Init(_DirectX::Get()->GetDevice(), _DirectX::Get()->GetCmandList());
	//ゲームシーン
	GameSceneManager::Get()->Initialize();
	GameSceneManager::Get()->Init(1);

	TitleScene::Get()->Initialize();
	TitleScene::Get()->Init();


	PostEffect::Get()->Initialize(_DirectX::Get()->GetDevice());

}

void SceneManagerh::Update()
{
	Input::Get()->Update();

	if (scene == Title)
	{
		if (Input::Get()->KeybordTrigger(DIK_SPACE))
		{
			scene = SelectScene;
			StageSelect::Get()->Init();
		}
	}
	else if (scene == SelectScene)
	{
		if (Input::Get()->KeybordTrigger(DIK_SPACE))
		{
			scene = GameScene;
			GameSceneManager::Get()->Init(StageSelect::Get()->GetStageNum());
		}
	}
	else if (scene == GameScene)
	{
		if (GameSceneManager::Get()->GetChangeScene())
		{
			scene = Title;
		}
	}

	if (scene == Title)
	{
		TitleScene::Get()->Update();
	}
	else if (scene == SelectScene)
	{
		StageSelect::Get()->Update();
	}
	else if (scene == GameScene)
	{
		GameSceneManager::Get()->Update();
	}
}

void SceneManagerh::Draw()
{
	//描画開始

	//オブジェクト描画前処理
	Object::Get()->PreDraw();
	Sprite::Get()->PreDraw();
	PostEffect::Get()->PreDrawScene(_DirectX::Get()->GetCmandList());
	if (scene == Title)
	{
		TitleScene::Get()->Draw();
	}
	else if (scene == SelectScene)
	{
		StageSelect::Get()->Draw();
	}
	else if (scene == GameScene)
	{
		GameSceneManager::Get()->Draw();
	}

	DebugText::Get()->DrawAll();
	PostEffect::Get()->PostDrawScene(_DirectX::Get()->GetCmandList());

	_DirectX::Get()->PreDraw();
	//ポストエフェクトの描画
	PostEffect::Get()->Draw(_DirectX::Get()->GetCmandList());
	_DirectX::Get()->ResourceBarrier();
}
