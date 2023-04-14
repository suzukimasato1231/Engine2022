#include "SceneManager.h"
#include<sstream>
#include<iomanip>
#include "Input.h"
#include"Shape.h"
#include"PostEffect.h"
#include"GameScene.h"
#include"TitleScene.h"
#include"StageSelect.h"
#include"ResultScene.h"
SceneManager::SceneManager()
{}
SceneManager::~SceneManager()
{
	//XAudio2解放
	Audio::Get()->xAudio2.Reset();
	//音データ解放
	Audio::SoundUnload(&m_bgm);
	scene_->Finalize();
	delete scene_;
}
void SceneManager::Initialize()
{
	//汎用機能
	//ゲームウィンドウの作成
	Window::Get()->CreateGameWindow();
	// DirectX初期化処理
	DirectXBase::Get()->Initilize();
	//入力の初期化
	Input::Get()->Initialize();
	//シェーダーの読み込み
	ShaderManager::LoadShaders();
	//ライト静的初期化
	LightGroup::StaticInitialize(DirectXBase::Get()->GetDevice());
	//スプライト静的初期化
	Sprite::StaticInit(DirectXBase::Get()->GetDevice(), DirectXBase::Get()->GetCmandList());
	//テキストクラス初期化
	Texture::Get()->Init(DirectXBase::Get()->GetDevice());
	Pipeline::CreatePipeline(DirectXBase::Get()->GetDevice());
	//デバックテキスト初期化
	DebugText::Get()->Initialize();
	//スプライトクラス作成
	Sprite::Get()->Init();
	//FBX初期化
	FbxLoader::GetInstance()->Initialize(DirectXBase::Get()->GetDevice());
	FBXObject3d::SetDevice(DirectXBase::Get()->GetDevice());
	FBXObject3d::SetCmdList(DirectXBase::Get()->GetCmandList());
	FBXObject3d::CreateGraphicsPipeline();
	FBXObject3d::CreateShadowPipeline();
	//図形モデル初期化
	Shape::Init(DirectXBase::Get()->GetDevice());
	//パーティクル初期化
	ParticleManager::StaticInitialize(DirectXBase::Get()->GetDevice(), DirectXBase::Get()->GetCmandList(), window_width, window_height);
	//3Dオブジェクト初期化
	Object::Init(DirectXBase::Get()->GetDevice(), DirectXBase::Get()->GetCmandList());

	PostEffect::Get()->Initialize(DirectXBase::Get()->GetDevice());
	////影
	m_shadowMapFar.Init();
	Texture::Get()->LoadShadowTexture(m_shadowMapFar.GetTexbuff());
	Texture::Get()->LoadCameraTexture(PostEffect::Get()->GetDepth());

	//音作成
	Audio::Get()->Init();
	//プレイヤーの初期化
	Player::Get()->Init();
	//ステージ
	Stage::Get()->Init();
	//シーンをタイトルに設定
	BaseScene* scene = new TitleScene();
	SetNextScene(scene);


	m_changeBlack = Sprite::Get()->SpriteCreate(L"Resources/black.png");

	//BGM
	m_bgm = Audio::SoundLoadWave("Resources/sound/BGM/bgm.wav");
	Audio::Get()->SoundBGMPlayLoopWave(m_bgm, 0);
	Audio::Get()->SetVolume(0.02f);
}

void SceneManager::Update()
{
	Input::Get()->Update();

	//シーンチェンジ
	SceneChange();

	//次のシーンの予約があるなら
	if (m_changeSceneFlag == ChangeEnd && nextScene_)
	{
		if (scene_)
		{
			scene_->Finalize();
			delete scene_;
		}
		//シーン切り替え
		scene_ = nextScene_;
		nextScene_ = nullptr;

		scene_->SetSceneManager(this);
		//次のシーンを初期化する
		scene_->Init(m_stageNum);
	}
	//更新
	scene_->Update(m_stageNum, m_breakBox);

	if (Input::Get()->KeybordTrigger(DIK_T) == true)
	{
		BaseScene* scene = new TitleScene();
		SetNextScene(scene);
	}
}

void SceneManager::Draw()
{
	//影深度値取得
	m_shadowMapFar.PreDraw(DirectXBase::Get()->GetCmandList());
	Object::InitDraw();
	//影描画
	scene_->ShadowDraw();
	m_shadowMapFar.PostDraw(DirectXBase::Get()->GetCmandList());


	PostEffect::Get()->PreDrawScene(DirectXBase::Get()->GetCmandList());
	Object::InitDraw(), Sprite::Get()->PreDraw();
	//カメラ目線の描画
	scene_->Draw(m_stageNum);
	DebugText::Get()->DrawAll();
	if (m_changeSceneFlag == ChangeFirst || m_changeSceneFlag == ChangeEnd)
	{
		Sprite::Get()->Draw(m_changeBlack, Vec2(), static_cast<float>(window_width), static_cast<float>(window_height), Vec2(), m_changeSceneColor);
	}
	PostEffect::Get()->PostDrawScene(DirectXBase::Get()->GetCmandList());

	DirectXBase::Get()->PreDraw();
	////ポストエフェクトの描画
	PostEffect::Get()->Draw(DirectXBase::Get()->GetCmandList());
	//UI描画
	scene_->SecondDraw();
	DirectXBase::Get()->ResourceBarrier();
}

void SceneManager::Delete()
{
	Object::Delete();
}

void SceneManager::SceneChange()
{
	//シーンチェンジ開始
	if (nextScene_ && m_changeSceneFlag == ChangeEmpty)
	{
		m_changeSceneFlag = ChangeFirst;
	}

	//シーンチェンジの色
	if (m_changeSceneFlag == ChangeFirst)
	{
		m_changeSceneColor += Vec4(0.0f, 0.0f, 0.0f, 0.1f);
		if (m_changeSceneColor.w >= 1.0f)
		{
			m_changeSceneFlag = ChangeEnd;
		}
	}
	else if (m_changeSceneFlag == ChangeEnd)
	{
		m_changeSceneColor -= Vec4(0.0f, 0.0f, 0.0f, 0.1f);
		if (m_changeSceneColor.w <= 0.0f)
		{
			m_changeSceneFlag = ChangeEmpty;
		}
	}
}