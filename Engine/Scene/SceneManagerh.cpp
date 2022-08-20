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
	Pipeline::CreatePipeline(_DirectX::Get()->GetDevice());
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

	titleScene.Initialize();
	//ゲームシーン
	gameScene.Initialize();
	gameScene.Init(0);
	stageScene.Initialize();
	resultScene.Init();
	PostEffect::Get()->Initialize(_DirectX::Get()->GetDevice());
	//影
	ShadowMap::Get()->Init();
	Texture::Get()->LoadShadowTexture(ShadowMap::Get()->GetTexbuff());
	titleScene.Init();
}

void SceneManagerh::Update()
{
	Input::Get()->Update();
	//シーン切り替え
	if (scene == Title)
	{
		if (Input::Get()->KeybordTrigger(DIK_SPACE) || Input::Get()->ControllerDown(ButtonA))
		{
			scene = SelectScene;
			stageScene.Init();
		}
	}
	else if (scene == SelectScene)
	{
		if (stageScene.GetSelectFlag() == true)
		{
			scene = GameScene;
			gameScene.Init(stageScene.GetStageNum());
		}
	}
	else if (scene == GameScene)
	{
		if (gameScene.GetChangeScene())
		{
			scene = Result;
			resultScene.Init();
		}
	}
	else if (scene == Result)
	{
		if (Input::Get()->KeybordTrigger(DIK_SPACE) || Input::Get()->ControllerDown(ButtonA))
		{
			scene = Title;
			titleScene.Init();
		}
	}
	//更新
	if (scene == Title)
	{
		titleScene.Update();
	}
	else if (scene == SelectScene)
	{
		stageScene.Update();
	}
	else if (scene == GameScene)
	{
		gameScene.Update();
	}
	else if (scene == Result)
	{
		resultScene.Update();
	}
}

void SceneManagerh::Draw()
{
	//描画開始

	//影深度値取得
	ShadowMap::Get()->PreDraw(_DirectX::Get()->GetCmandList());
	Object::Get()->PreDraw(), Sprite::Get()->PreDraw();
	if (scene == Title)
	{
	}
	else if (scene == SelectScene)
	{
		stageScene.DrawShadow();
	}
	else if (scene == GameScene)
	{
		gameScene.ShadowDraw();
	}
	else if (scene == Result)
	{
	}
	ShadowMap::Get()->PostDraw(_DirectX::Get()->GetCmandList());



	PostEffect::Get()->PreDrawScene(_DirectX::Get()->GetCmandList());
	Object::Get()->PreDraw(), Sprite::Get()->PreDraw();
	//カメラ目線の描画
	Object::SetPipeline(Pipeline::OBJPipeline);
	if (scene == Title)
	{
		titleScene.Draw();
	}
	else if (scene == SelectScene)
	{
		stageScene.Draw();
	}
	else if (scene == GameScene)
	{
		/*if (Input::Get()->KeybordTrigger(DIK_C))
		{
			if (Flag == false){	Flag = true;}
			else { Flag = false; }
		}*/
		//if (Flag == false){
		gameScene.Draw();
		/*}
		else {
			ShadowMap::Get()->Draw(_DirectX::Get()->GetCmandList());
		}*/
	}
	else if (scene == Result)
	{
		resultScene.Draw();
	}
	DebugText::Get()->DrawAll();
	PostEffect::Get()->PostDrawScene(_DirectX::Get()->GetCmandList());

	_DirectX::Get()->PreDraw();
	//ポストエフェクトの描画
	PostEffect::Get()->Draw(_DirectX::Get()->GetCmandList());
	_DirectX::Get()->ResourceBarrier();

}
