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
	//XAudio2解放
	Audio::Get()->xAudio2.Reset();
	//音データ解放
	Audio::SoundUnload(&bgm);
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

	PostEffect::Get()->Initialize(_DirectX::Get()->GetDevice());
	////影
	ShadowMap::Get()->Init();
	Texture::Get()->LoadShadowTexture(ShadowMap::Get()->GetTexbuff());
	Texture::Get()->LoadCameraTexture(PostEffect::Get()->GetDepth());

	//音作成
	Audio::Get()->Init();
	titleScene.Initialize();
	////ゲームシーン
	gameScene.Initialize();
	gameScene.Init(0);
	stageScene.Initialize();
	resultScene.Initialize();
	resultScene.Init();
	titleScene.Init();

	changeBlack = Sprite::Get()->SpriteCreate(L"Resources/black.png");

	//BGM
	bgm = Audio::SoundLoadWave("Resources/sound/BGM/bgm.wav");
	Audio::Get()->SoundBGMPlayLoopWave(bgm, 0);
	Audio::Get()->SetVolume(0.02f);
}

void SceneManagerh::Update()
{
	Input::Get()->Update();

	//シーン切り替え
	if (scene == Title)
	{
		if (changeSceneFlag == ChangeStand && (Input::Get()->KeybordTrigger(DIK_SPACE) || Input::Get()->ControllerDown(ButtonA)))
		{
			changeSceneFlag = ChangeFirst;
			sceneMe = SelectScene;
		}
	}
	else if (scene == SelectScene)
	{
		if (changeSceneFlag == ChangeStand && stageScene.GetSelectFlag() == true)
		{
			sceneMe = GameScene;
			changeSceneFlag = ChangeFirst;
		}
	}
	else if (scene == GameScene)
	{
		if (changeSceneFlag == ChangeStand && gameScene.GetChangeScene())
		{
			if (gameScene.GetChangeNum() == 0)
			{
				sceneMe = Result;
			}
			else if (gameScene.GetChangeNum() == 1)
			{
				sceneMe = GameScene;
			}
			else if (gameScene.GetChangeNum() == 2)
			{
				sceneMe = SelectScene;
			}
			changeSceneFlag = ChangeFirst;
		}
	}
	else if (scene == Result)
	{
		if (changeSceneFlag == ChangeStand && (Input::Get()->KeybordTrigger(DIK_SPACE) || Input::Get()->ControllerDown(ButtonA)))
		{
			if (resultScene.GetScene() == ResultNextStage&&stageScene.GetStageNum()!=3)
			{
				sceneMe = GameScene;
			}
			if (resultScene.GetScene() == ResultSelect || stageScene.GetStageNum() == 3)
			{
				sceneMe = SelectScene;
			}
			changeSceneFlag = ChangeFirst;
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


	//シーンチェンジ
	if (changeSceneFlag == ChangeFirst)
	{
		changeSceneColor += Vec4(0.0f, 0.0f, 0.0f, 0.1f);
		if (changeSceneColor.w >= 1.0f)
		{
			changeSceneFlag = ChangeEnd;
			switch (scene)
			{
			case Title:
				stageScene.Init();
				break;
			case SelectScene:
				gameScene.Init(stageScene.GetStageNum());
				break;
			case GameScene:
				if (sceneMe == Result)
				{
					resultScene.Init();
				}
				else if (sceneMe == GameScene)
				{
					gameScene.Init(stageScene.GetStageNum());
				}
				else if (sceneMe == SelectScene)
				{
					stageScene.Init();
				}
				break;
			case Result:
				if (sceneMe == GameScene)
				{
					stageScene.StagePlas();
					gameScene.Init(stageScene.GetStageNum());
					
				}
				else if (sceneMe == SelectScene)
				{
					stageScene.Init();
				}
				break;
			default:
				break;
			}
			scene = sceneMe;
		}
	}
	else if (changeSceneFlag == ChangeEnd)
	{
		changeSceneColor -= Vec4(0.0f, 0.0f, 0.0f, 0.1f);
		if (changeSceneColor.w <= 0.0f)
		{
			changeSceneFlag = ChangeStand;
		}
	}


	if (Input::Get()->KeybordTrigger(DIK_T) == true)
	{
		scene = Title;
		titleScene.Init();
	}
}

void SceneManagerh::Draw()
{
	//影深度値取得
	ShadowMap::Get()->PreDraw(_DirectX::Get()->GetCmandList());
	Object::Get()->PreDraw(), Object::InitDraw(), Sprite::Get()->PreDraw();
	if (scene == Title)
	{
		titleScene.ShadowDraw();
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
		resultScene.ShadowDraw();
	}
	ShadowMap::Get()->PostDraw(_DirectX::Get()->GetCmandList());

	PostEffect::Get()->PreDrawScene(_DirectX::Get()->GetCmandList());
	Object::SetPipeline(Pipeline::OBJPipeline);
	Object::Get()->PreDraw(true), Object::InitDraw(), Sprite::Get()->PreDraw();
	//カメラ目線の描画
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
		gameScene.Draw();
		//ShadowMap::Get()->Draw(_DirectX::Get()->GetCmandList());
	}
	else if (scene == Result)
	{
		resultScene.Draw(stageScene.GetStageNum());
	}
	DebugText::Get()->DrawAll();
	if (changeSceneFlag == ChangeFirst || changeSceneFlag == ChangeEnd)
	{
		Sprite::Get()->Draw(changeBlack, Vec2(), static_cast<float>(window_width), static_cast<float>(window_height), Vec2(), changeSceneColor);
	}
	PostEffect::Get()->PostDrawScene(_DirectX::Get()->GetCmandList());

	_DirectX::Get()->PreDraw();

	////ポストエフェクトの描画
	//PostEffect::Get()->SetPipeline(1);
	PostEffect::Get()->Draw(_DirectX::Get()->GetCmandList());

	_DirectX::Get()->ResourceBarrier();
}

void SceneManagerh::Delete()
{
	titleScene.Delete();
	resultScene.Delete();
}
